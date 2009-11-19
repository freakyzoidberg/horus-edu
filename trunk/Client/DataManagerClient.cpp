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
	QMutexLocker(&data->mutex);
	quint8 oldStatus = data->status();

	// data must be EMPTY or UPTODATE before
	// and must being set to UPDATING, CREATING, SAVING or DELETING
	if ((oldStatus != Data::EMPTY && oldStatus != Data::UPTODATE && oldStatus != Data::CACHED) ||
		(newStatus != Data::UPDATING && newStatus != Data::CREATING && newStatus != Data::SAVING && newStatus != Data::DELETING))
	{
		//hack for forum, must decomment
		//qWarning() << tr("Data") << data << tr("try to chage status from") << (Data::DataStatus)oldStatus << tr("to") << (Data::DataStatus)newStatus << tr("which is not authorized.");
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

	if (status != Data::UPDATED && status != Data::SAVED && status != Data::CREATED && status != Data::DELETED && status != Data::_ERROR_)
	{
		//hack for forum, must decomment
		//qWarning() << tr("DataManagerClient received a status") << (Data::DataStatus)status << tr("which is not authorized.");
		return;
	}

	Data* data;
	if (status == Data::CREATED)
	{
		QByteArray oldKey;
		stream >> oldKey;
		QDataStream streamOldKey(oldKey);
		data = plugin->dataWithKey(streamOldKey);
	}
	else
		data = plugin->dataWithKey(stream);

	QMutexLocker(&data->mutex);

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
	else if (status == Data::SAVED)
	{
		data->_status = Data::UPTODATE;
		emit data->updated();
		emit plugin->dataUpdated(data);
	}
	else if (status == Data::_ERROR_)
	{
		quint8 error;
		stream >> error;
		qDebug() << "Data: Error received:" << (Data::Error)error << data;
		emit data->error((Data::Error)error);
		emit plugin->dataError(data, (Data::Error)error);
	}
}

void DataManagerClient::sendData(UserData*, Data* data) const
{
	QMutexLocker(&data->mutex);
	CommData packet(data->dataType());
    QDataStream stream(&packet.data, QIODevice::WriteOnly);
	quint8 status = data->status();

	if (status != Data::UPDATING && status != Data::DELETING && status != Data::CREATING && status != Data::SAVING)
	{
		//hack for forum, must decomment
		//qWarning() << tr("Data") << data << tr("try to be send with status") << (Data::DataStatus)status << tr("which is not authorized.");
		return;
	}

	stream << status;

	data->keyToStream(stream);

	if (status == Data::CREATING || status == Data::SAVING)
		data->dataToStream(stream);

	QMetaObject::invokeMethod(NetworkManager::instance(), "sendPacket", Q_ARG(const QByteArray, packet.getPacket()));
}
