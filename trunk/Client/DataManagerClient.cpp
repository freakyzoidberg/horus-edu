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
	quint8 oldStatus = data->status();

	// data must be EMPTY or UPTODATE before
	// and must being set to UPDATING, CREATING, SAVING or DELETING
	if ((oldStatus != Data::EMPTY && oldStatus != Data::UPTODATE) ||
		(newStatus != Data::UPDATING && newStatus != Data::CREATING && newStatus != Data::SAVING && newStatus != Data::DELETING))
	{
		qWarning() << tr("Data") << data << tr("try to chage status from") << oldStatus << tr("to") << newStatus << tr("which is not authorized.");
		return;
	}

	data->_status = newStatus;
	sendData(0, data);
}

void DataManagerClient::receiveData(UserData*, const QByteArray& d) const
{
	QDataStream stream(d); // ReadOnly
    quint8    status,   error;
	stream >> status >> error;

	if (status != Data::UPTODATE && status != Data::SAVED && status != Data::CREATED && status != Data::DELETED)
	{
		qWarning() << tr("DataManagerClient received a status") << status << tr("which is not authorized.");
		return;
	}


	Data* data;
	if (status == Data::CREATED)
	{
		QByteArray oldKey;
		stream >> oldKey;
		QDataStream streamOldKey(oldKey);
		data = plugin->getDataWithKey(streamOldKey);
	}
	else
		data = plugin->getDataWithKey(stream);

	QMutexLocker(data->lock);

	if (status == Data::CREATED)
	{
		plugin->dataHaveNewKey(data, stream);
	}

	if (status == Data::UPTODATE && ! error)
		data->dataFromStream(stream);

	data->_status = Data::UPTODATE;
	emit data->updated();
	emit plugin->dataUpdated(data);
	data->setError(error);
	if (error)
		qDebug() << "error data received:" << error;
}

void DataManagerClient::sendData(UserData*, Data* data) const
{
    CommData packet(data->getDataType());
    QDataStream stream(&packet.data, QIODevice::WriteOnly);
	quint8 status = data->status();

	if (status != Data::UPDATING && status != Data::DELETING && status != Data::CREATING && status != Data::SAVING)
	{
		qWarning() << tr("Data") << data << tr("try to be send with status") << status << tr("which is not authorized.");
		return;
	}

	stream << status;

	data->keyToStream(stream);

	if (status == Data::CREATING || status == Data::SAVING)
		data->dataToStream(stream);

    QCoreApplication::postEvent(MetaManager::getInstance()->findManager("NetworkManager"), new SendPacketEvent(packet.getPacket()));
}
