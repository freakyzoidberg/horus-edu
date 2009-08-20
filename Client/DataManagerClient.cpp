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

    ///// UPDATING /////
    // if a client ask for an update of the data
    if (newStatus == Data::UPDATING &&
        // and if this data is up-to-date, empty or cached
        (data->status() == Data::UPTODATE || data->status() == Data::EMPTY || data->status() == Data::CACHED))
    {
        data->_status = Data::UPDATING;
        return sendData(plugin->pluginManager->currentUser(), data);
    }

    ///// CREATING /////
    // if a client want to create a new data
//    if (newStatus == Data::CREATING)
//    {
//    }

    ///// SAVING /////
    // if a client save a modified value of the data
    if (newStatus == Data::SAVING &&
        // and if this data is is up-to-date or cached
        (data->status() == Data::UPTODATE || data->status() == Data::CACHED))
    {
        data->_status = Data::SAVING;
        return sendData(plugin->pluginManager->currentUser(), data);
    }

    ///// DELETING /////
    // if a client delete a data
//    if (newStatus == Data::DELETING)
//    {
//    }
//    if (data->status() == Data::EMPTY && newStatus == Data::UPTODATE)

    data->_status = newStatus;
}


void DataManagerClient::receiveData(UserData* user, const QByteArray& d) const
{
    QDataStream stream(d); //ReadOnly
    quint8    status,   error;
    stream >> status >> error;

    if (status == Data::EMPTY)
        return;

    Data* data = plugin->getDataWithKey(stream);
    QMutexLocker(data->lock);
    if ( ! error)
        //TODO: do not always read data
        data->dataFromStream(stream);

    data->setStatus(status);
    data->setError(error);
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
