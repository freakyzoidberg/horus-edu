#include "DataManagerServer.h"
#include "../Common/DataPlugin.h"
#include "../Common/CommData.h"
#include "../Common/Data.h"

#include "Sql.h"
#include "ClientSocket.h"
#include "PluginManagerServer.h"

#include <QMetaObject>

void DataManagerServer::dataStatusChange(Data* data, quint8 newStatus) const
{
    Sql conn;
    QSqlQuery query(QSqlDatabase::database(conn));
    QMutexLocker(data->lock);

    // if the data is not in memory on the server, loading from database
    if (data->status() == Data::EMPTY)
    {
        data->fillFromDatabase(query);
        data->_status = Data::UPTODATE;
    }

    // if a client ask for a data, send him the data
    if (newStatus == Data::UPDATING)
        return sendData(PluginManagerServer::instance()->currentUser(), data);

    // if a client want to create a new data
//    if (newStatus == Data::CREATING)
//    {
//    }

    // if a client save a new value of the data
    if (newStatus == Data::SAVING)
    {
        data->saveIntoDatabase(query);
        data->setStatus(Data::UPTODATE);
        return sendData(PluginManagerServer::instance()->currentUser(), data);
    }

    // if a client delete a data
//    if (newStatus == Data::DELETING)
//    {
//    }
}

void DataManagerServer::receiveData(UserData* user, const QByteArray& d) const
{
    QDataStream stream(d); //ReadOnly
    quint8    status,   error;
    stream >> status >> error;

    if (status == Data::EMPTY)
        return;

    Data* data = plugin->getDataWithKey(stream);
    QMutexLocker(data->lock);
    if ( ! error)
    {
        //TODO: do not always write data
        data->dataFromStream(stream);
    }

    data->setStatus(status);
    data->setError(error);
    qDebug() << "receiveData" << data;
}

void DataManagerServer::sendData(UserData* user, Data* data) const
{
    QMutexLocker(data->lock);
    CommData packet(data->getDataType());
    QDataStream stream(&packet.data, QIODevice::WriteOnly);
    stream << data->status() << data->error();

    if (data->status() == Data::EMPTY)
        return;

    data->keyToStream(stream);
    if ( ! data->error())
        //TODO: do not always write data
        data->dataToStream(stream);

    ClientSocket* socket = ClientSocket::connectedUsers.value( user );
    if (socket)
       QMetaObject::invokeMethod(socket, "sendPacket", Qt::QueuedConnection, Q_ARG(QByteArray, packet.getPacket()));
    else
        qDebug() << "DataManagerServer::sendData error user not connected";
}
