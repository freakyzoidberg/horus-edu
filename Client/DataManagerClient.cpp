#include "DataManagerClient.h"

#include <QEvent>
#include <QtDebug>

#include "../Common/CommData.h"
#include "../Common/UserData.h"
#include "../Common/Data.h"

#include "PluginManagerClient.h"
#include "NetworkManager.h"

void DataManagerClient::dataStatusChange(Data* data, quint8 newStatus) const
{
    QMutexLocker(data->lock);
	quint8 oldStatus = data->status();

	// data must be EMPTY or UPTODATE before
	// and must being set to UPDATING, CREATING, SAVING or DELETING
	if ((oldStatus != Data::EMPTY && oldStatus != Data::UPTODATE && oldStatus != Data::CACHED) ||
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
	quint8    status;
	stream >> status;

	if (status != Data::UPDATED && status != Data::SAVED && status != Data::CREATED && status != Data::DELETED)
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
		data->_status = Data::UPTODATE;
		emit data->created();
		emit plugin->dataCreated(data);

		emit data->updated();
		emit plugin->dataUpdated(data);
	}
	else if (status == Data::UPDATED)
	{
		data->dataFromStream(stream);
		data->_status = Data::UPTODATE;
		emit data->updated();
		emit plugin->dataUpdated(data);
	}
	else if (status == Data::DELETED)
	{
		data->_status = Data::DELETED;
		emit data->removed();
		emit plugin->dataRemoved(data);
	}
	else if (status == Data::ERROR)
	{
		quint8 error;
		stream >> error;
		qDebug() << "error data received:" << error;
		emit data->error((Data::Error)error);
		emit plugin->dataError(data, (Data::Error)error);
	}
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

	QMetaObject::invokeMethod(NetworkManager::instance(), "sendPacket", Q_ARG(const QByteArray, packet.getPacket()));
}
