#include "DataManagerServer.h"
#include "../Common/DataPlugin.h"
#include "../Common/CommData.h"
#include "../Common/Data.h"

#include "Sql.h"
#include "ClientSocket.h"

#include <QMetaObject>

void DataManagerServer::dataStatusChange(UserData* user, Data* data, quint8 newStatus) const
{
//    QMutexLocker(data->lock);

    // if the data is not in memory on the server, loading from database
    if (data->status() == Data::EMPTY)
    {
        Sql conn;
        QSqlQuery query(QSqlDatabase::database(conn));
        data->fillFromDatabase(query);
        data->_status = Data::UPTODATE;
    }

    // if a client ask for a data, send him the data
    if (newStatus == Data::UPDATING)
        return sendData(user, data);

    // if a client want to create a new data
    if (newStatus == Data::CREATING)
    {
    }
    // if a client save a new value of the data
    if (newStatus == Data::SAVING)
    {
    }
    // if a client delete a data
    if (newStatus == Data::DELETING)
    {
    }
}

void DataManagerServer::receiveData(UserData* user, const QByteArray& d) const
{
    QDataStream stream(d); //ReadOnly
    quint8    status,   error;
    stream >> status >> error;

    if (status == Data::EMPTY)
        return;

    Data* data = plugin->getDataWithKey(stream);
    if ( ! data->error())
    {
        //TODO: do not always write data
        data->dataFromStream(stream);
    }

    data->setStatus(user, status);
    data->setError(error);
}

void DataManagerServer::sendData(UserData* user, Data* data) const
{
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
