#include "DataManagerClient.h"

#include <QEvent>
#include <QCoreApplication>

#include "../Common/CommData.h"
#include "../Common/UserData.h"
#include "../Common/Data.h"

#include "PluginManagerClient.h"
#include "MetaManager.h"
#include "ClientEvents.h"

void DataManagerClient::dataStatusChange(Data* data, quint8 newStatus) const
{
    QMutexLocker(data->lock);

    // if a client ask for a data, send him the data
    if (newStatus == Data::UPDATING)
    {
        data->_status = Data::UPDATING;
        return sendData(MetaManager::getInstance()->findManager<PluginManager *>()->currentUser(), data);
    }

    // if a client want to create a new data
//    if (newStatus == Data::CREATING)
//    {
//    }
    // if a client save a new value of the data
    if (newStatus == Data::SAVING)
    {
        data->_status = Data::UPDATING;
        return sendData(MetaManager::getInstance()->findManager<PluginManager *>()->currentUser(), data);
    }
    // if a client delete a data
//    if (newStatus == Data::DELETING)
//    {
//    }
//    if (data->status() == Data::EMPTY && newStatus == Data::UPTODATE)
        data->_status = newStatus;
}


void DataManagerClient::receiveData(UserData* user, const QByteArray& d) const
{
    qDebug() << d.toHex();
    QDataStream stream(d); //ReadOnly
    quint8    status,   error;
    stream >> status >> error;

    if (status == Data::EMPTY)
        return;

    Data* data = plugin->getDataWithKey(stream);
    if ( ! error)
    {
        //TODO: do not always read data
        data->dataFromStream(stream);
    }

    data->setStatus(status);
    data->setError(error);
    qDebug() << "DataManagerClient::receiveData" << data;
}

void DataManagerClient::sendData(UserData* user, Data* data) const
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
	QCoreApplication::postEvent(MetaManager::getInstance()->findManager("NetworkManager"), new SendPacketEvent(packet.getPacket()));
}
