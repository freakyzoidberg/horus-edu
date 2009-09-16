#include "DataManagerServer.h"
#include "../Common/DataPlugin.h"
#include "../Common/CommData.h"
#include "../Common/Data.h"

#include "Sql.h"
#include "ClientSocket.h"
#include "PluginManagerServer.h"

#include <QHash>
#include <QMetaObject>

void DataManagerServer::dataStatusChange(Data* data, quint8 newStatus) const
{
    Sql conn;
    QSqlQuery query(QSqlDatabase::database(conn));
    QMutexLocker(data->lock);
    quint8 oldStatus;
    const int maxStatus = 10;
    bool table[maxStatus][maxStatus] = {
    // EMPTY CACHED UPDATING SAVING CREATING DELETING UPTODATE SAVED CREATED DELETED <- Old Status / New Status |
    { false, false, false,   false, false,   false,   false,   false, false, false},              // EMPTY      v
    { false, false, false,   false, false,   false,   false,   false, false, false},              // CACHED
    {  true, false, false,   false, false,   false,    true,    true,  true, false},              // UPDATING
    {  true, false, false,   false, false,   false,    true,    true,  true, false},              // SAVING
    {  true, false, false,   false, false,   false,   false,   false, false, false},              // CREATING
    {  true, false, false,   false, false,   false,    true,    true,  true, false},              // DELETING
    { false, false, false,   false, false,   false,   false,   false, false, false},              // UPTODATE
    { false, false, false,   false, false,   false,   false,   false, false, false},              // SAVED
    { false, false, false,   false, false,   false,   false,   false, false, false},              // CREATED
    { false, false, false,   false, false,   false,   false,   false, false, false}};             // DELETED

    oldStatus = data->status();
    // if the data is not in memory on the server, loading from database
//    if (data->status() == Data::EMPTY && newStatus != Data::CREATING)
//    {
//        data->fillFromDatabase(query);
//        data->_status = Data::UPTODATE;
//    }
    if (table[newStatus][oldStatus])
    {
        // if a client want to create a new data
        if (newStatus == Data::CREATING)
        {
            QByteArray oldKey;
            QDataStream stream(&oldKey, QIODevice::ReadWrite);
            data->keyToStream(stream);
            data->createIntoDatabase(query);
            data->setStatus(Data::CREATED);
            sendCreatedData(PluginManagerServer::instance()->currentUser(), data, stream);
            return ;
        }
        // if a client save a new value of the data
        if (newStatus == Data::SAVING)
        {
            qDebug() << "DataManagerServer::saving data";

            data->saveIntoDatabase(query);

            //send the the user who save the data SAVED
            data->_status = Data::SAVED;
            sendData(PluginManagerServer::instance()->currentUser(), data);

            //send to the other user the data UPTODATE
            data->_status = Data::UPTODATE;
            foreach (UserData* u, ClientSocket::connectedUsers.keys())
                if (u != PluginManagerServer::instance()->currentUser())
                    sendData(u, data);
        }
        // if a client delete a data
        if (newStatus == Data::DELETING)
        {
            data->deleteFromDatabase(query);
            data->setStatus(Data::DELETED);
        }
    }
    else
    {
        data->setError(Data::PERMITION_DENIED);
        qDebug() << "DataManagerServer::error";
    }
}

void DataManagerServer::receiveData(UserData *, const QByteArray& d) const
{
    QDataStream stream(d); // ReadOnly
    quint8    status,   error;
    Data* data;
    
    stream >> status >> error;
    switch (status)
    {
    case Data::UPDATING:
    case Data::DELETING:
        data = plugin->getDataWithKey(stream);
        QMutexLocker(data->lock);
        break ;
    case Data::CREATING:
    case Data::SAVING:
        data = plugin->getDataWithKey(stream);
        QMutexLocker(data->lock);
        data->dataFromStream(stream);
        break ;
    default:
        qWarning() << "DataManagerServer::receiveData: plugin" << plugin << "received a data" << data->getDataType() << "with status" << data->status() << "from a client, which is unauthorized.";
    }
    data->setError(error);
    data->setStatus(status);
}

void DataManagerServer::sendData(UserData* user, Data* data) const
{
    QMutexLocker(data->lock);
    CommData packet(data->getDataType());
    QDataStream stream(&packet.data, QIODevice::WriteOnly);
    switch (data->status())
    {
    case Data::SAVED:
    case Data::DELETED:
        stream << data->status() << data->error();
        data->keyToStream(stream);
        break ;
    case Data::CREATED:
        stream << data->status() << data->error();
        data->keyToStream(stream);
        break ;
    case Data::UPTODATE:
        stream << data->status() << data->error();
        data->keyToStream(stream);
        if (!data->error())
            data->dataToStream(stream);
        break ;
    default:
        qWarning() << "DataManagerServer::sendData: plugin" << plugin << "try to send a data" << data->getDataType() << "with status" << data->status() << "to a client, which is unauthorized.";
        return ;
    }
    ClientSocket* socket = ClientSocket::connectedUsers.value(user);
    if (socket)
       QMetaObject::invokeMethod(socket, "sendPacket", Qt::QueuedConnection, Q_ARG(QByteArray, packet.getPacket()));
    else
        qWarning() << "DataManagerServer::sendData: user not connected";
    qDebug() << data;

}

void DataManagerServer::sendCreatedData(UserData *user, Data *data, QDataStream& oldKey) const
{
    QMutexLocker(data->lock);
    CommData packet(data->getDataType());
    QDataStream stream(&packet.data, QIODevice::WriteOnly);
    stream << Data::CREATED << data->error();
    data->keyToStream(stream);
    stream << oldKey;
    ClientSocket* socket = ClientSocket::connectedUsers.value(user);
    if (socket)
       QMetaObject::invokeMethod(socket, "sendPacket", Qt::QueuedConnection, Q_ARG(QByteArray, packet.getPacket()));
    else
        qWarning() << "DataManagerServer::sendData: user not connected";
}
