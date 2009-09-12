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
	QDataStream stream(d); // ReadOnly
    quint8    status,   error;
	Data *data;

	stream >> status >> error;
	switch (status)
	{
	case Data::SAVED:
	case Data::DELETED:
	    data = plugin->getDataWithKey(stream);
		QMutexLocker(data->lock);
		break ;
	case Data::UPTODATE:
	    data = plugin->getDataWithKey(stream);
		QMutexLocker(data->lock);
	    if (!error)
			data->dataFromStream(stream);
		break ;
	case Data::CREATED:
	    data = plugin->getDataWithKey(stream);
		QMutexLocker(data->lock);
	    if (!error)
			data->_plugin->dataHaveNewKey(data, stream);
		break ;
	default:
		qWarning() << "Plugin" << plugin->pluginName() << "receive data with status" << status << " from the server, which is unauthorized";
		return ;
	}
	data->_status = status;
    data->setError(error);
}

void DataManagerClient::sendData(UserData*, Data* data) const
{
    CommData packet(data->getDataType());
    QDataStream stream(&packet.data, QIODevice::WriteOnly);

	switch (data->status())
	{
	case Data::UPDATING:
	case Data::DELETING:
		stream << data->status() << data->error();
		data->keyToStream(stream);
		break ;
	case Data::CREATING:
	case Data::SAVING:
		stream << data->status() << data->error();
		data->keyToStream(stream);
		data->dataToStream(stream);
		break ;
	default:
		qWarning() << "Plugin" << plugin->pluginName() << "attempt to send data" << data->_plugin->pluginName() << "with status" << data->status() << "from the client, which is unauthorized";
		return ;
	}
    QCoreApplication::postEvent(MetaManager::getInstance()->findManager("NetworkManager"), new SendPacketEvent(packet.getPacket()));
}
