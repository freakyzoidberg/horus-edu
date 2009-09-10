#include "DataManagerClient.h"

#include <QEvent>
#include <QCoreApplication>
#include <QtDebug>

#include "../Common/CommData.h"
#include "../Common/UserData.h"
#include "../Common/Data.h"

#include "PluginManagerClient.h"
#include "MetaManager.h"
#include "ClientEvents.h"

void DataManagerClient::dataStatusChange(Data* data, quint8 newStatus) const
{
    QMutexLocker(data->lock);
	const int maxStatus = 10;
	bool table[maxStatus][maxStatus] = {
	// EMPTY CACHED UPDATING SAVING CREATING DELETING UPTODATE SAVED CREATED DELETED <- Old Status / New Status |
	{ false, false, false,   false, false,   false,   false,   false, false, false},              // EMPTY      v
	{ false, false, false,   false, false,   false,   false,   false, false, false},              // CACHED
	{  true,  true, false,   false, false,   false,   false,   false, false, false},              // UPDATING
	{ false,  true, false,   false, false,   false,    true,   false, false, false},              // SAVING
	{  true, false, false,   false, false,   false,   false,   false, false, false},              // CREATING
	{ false,  true, false,   false, false,   false,    true,   false, false, false},              // DELETING
	{ false, false, false,   false, false,   false,   false,   false, false, false},              // UPTODATE
	{ false, false, false,   false, false,   false,   false,   false, false, false},              // SAVED
	{ false, false, false,   false, false,   false,   false,   false, false, false},              // CREATED
	{ false, false, false,   false, false,   false,   false,   false, false, false}};             // DELETED

	if (table[newStatus][data->status()])
	{
		data->_status = newStatus;
		sendData(plugin->pluginManager->currentUser(), data);
	}
	else
	{
		qWarning() << "Plugin" << plugin->pluginName() << "attempt an unauthorized change of data" << data->_plugin->pluginName() << "from status" << data->_status << "to status" << newStatus;
		data->_status = newStatus;
	}
}


void DataManagerClient::receiveData(UserData*, const QByteArray& d) const
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

void DataManagerClient::sendData(UserData*, Data* data) const
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
