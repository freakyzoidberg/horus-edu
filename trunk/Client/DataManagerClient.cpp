#include "DataManagerClient.h"

#include <QMetaType>
#include <QDebug>

#include "../Common/CommData.h"
#include "../Common/UserData.h"

#include "PluginManagerClient.h"
#include "NetworkManager.h"

DataManagerClient::DataManagerClient(DataPlugin* plugin)
{
	_plugin = plugin;
	qRegisterMetaType<Data*>("Data*");
}

void DataManagerClient::dataStatusChange(Data* data, quint8 newStatus)
{
	QMutexLocker(&data->mutex);
	quint8 oldStatus = data->status();

	if (newStatus == Data::SAVING && (oldStatus == Data::CREATING || oldStatus == Data::SAVING))
	{
		if ( ! _needSaveAgain.contains(data))
			_needSaveAgain.append(data);
		return;
	}

	// data must be EMPTY, UPTODATE or CACHED before
	// and must being set to CREATING, SAVING or DELETING
	if ((oldStatus != Data::EMPTY && oldStatus != Data::UPTODATE && oldStatus != Data::CACHED) ||
		(newStatus != Data::CREATING && newStatus != Data::SAVING && newStatus != Data::REMOVING))
	{
		qDebug() << tr("Should not happen:") << data << tr("chage status from") << (Data::Status)oldStatus << tr("to") << (Data::Status)newStatus;
		return;
	}

	data->_status = newStatus;
	if (newStatus == Data::CREATING)
		emit _plugin->dataCreated(data);
	else if (newStatus == Data::REMOVING)
	{
		emit data->removed();
		emit _plugin->dataRemoved(data);
	}
	emit data->statusChanged();
	emit _plugin->dataStatusChanged(data);
	sendData(data);
}

void DataManagerClient::receiveData(const QByteArray& d)
{
	QDataStream stream(d); // ReadOnly
	quint8    status;
	stream >> status;

	if (status != Data::UPDATED && status != Data::SAVED && status != Data::CREATED && status != Data::REMOVED && status != Data::DATA_ERROR)
	{
		qDebug() << tr("Should not happen:") <<  tr("DataManager receive status") << (Data::Status)status;
		return;
	}

	Data* data;
	if (status == Data::CREATED)
	{
		QByteArray oldKey;
		stream >> oldKey;
		QDataStream streamOldKey(oldKey);
		data = _plugin->dataWithKey(streamOldKey);
	}
	else
		data = _plugin->dataWithKey(stream);

	QMutexLocker(&data->mutex);
	quint8 oldStatus = data->_status;

	if (status == Data::CREATED)
	{
		_plugin->dataHaveNewKey(data, stream);
		data->_status = Data::UPTODATE;
		emit data->statusChanged();
		emit _plugin->dataStatusChanged(data);
		emit data->updated();
		emit _plugin->dataUpdated(data);
		if (_needSaveAgain.contains(data))
		{
			_needSaveAgain.removeOne(data);
			data->save();
		}
	}
	else if (status == Data::UPDATED)
	{
		data->dataFromStream(stream);
		data->_status = Data::UPTODATE;
		emit data->statusChanged();
		emit _plugin->dataStatusChanged(data);
		emit data->updated();
		emit _plugin->dataUpdated(data);
	}
	else if (status == Data::REMOVED)
	{
		data->_status = Data::REMOVED;
		emit data->statusChanged();
		emit _plugin->dataStatusChanged(data);
		emit data->removed();
		emit _plugin->dataRemoved(data);
		_plugin->_allDatas.removeOne(data);
		delete data;
	}
	else if (status == Data::SAVED)
	{
		data->_status = Data::UPTODATE;
		emit data->statusChanged();
		emit _plugin->dataStatusChanged(data);
		emit data->updated();
		emit _plugin->dataUpdated(data);

		if (_needSaveAgain.contains(data))
		{
			_needSaveAgain.removeOne(data);
			data->save();
		}
	}
	else if (status == Data::DATA_ERROR)
	{
		quint8 error;
		quint8 tmpStatus;
		stream >> error >> tmpStatus;
		qWarning() << "Data Error received:" << (Data::Error)error << (Data::Status)tmpStatus << data;

		emit data->error((Data::Error)error);
		emit _plugin->dataError(data, (Data::Error)error);

		if (tmpStatus == Data::UPTODATE)
		{
			data->dataFromStream(stream);
			data->_status = Data::UPTODATE;
			emit data->statusChanged();
			emit _plugin->dataStatusChanged(data);
			emit data->updated();
			emit _plugin->dataUpdated(data);
		}

		if (tmpStatus == Data::REMOVED)
		{
			data->_status = Data::REMOVED;
			emit data->statusChanged();
			emit _plugin->dataStatusChanged(data);
			_plugin->_allDatas.removeOne(data);
			delete data;
		}
	}
	if (_dependantDatas.contains(data))
	{
		Data* dep = _dependantDatas.take(data);
		sendData(dep);
	}
}

void DataManagerClient::sendData(Data* data)
{
	QMutexLocker(&data->mutex);
	foreach (Data* dep, data->dependsOfCreatedData())
		if (dep->status() == Data::EMPTY || dep->status() == Data::CREATING)
		{
			_dependantDatas.insert(dep, data);
			return;
		}

	CommData packet(data->dataType());
    QDataStream stream(&packet.data, QIODevice::WriteOnly);
	quint8 status = data->status();

	if (status != Data::REMOVING && status != Data::CREATING && status != Data::SAVING)
	{
		qDebug() << tr("Should not happen:") << data << tr("is sent with status") << (Data::Status)status;
		return;
	}

	stream << status;

	data->keyToStream(stream);

	if (status == Data::CREATING || status == Data::SAVING)
		data->dataToStream(stream);

	QMetaObject::invokeMethod(NetworkManager::instance(), "sendPacket", Q_ARG(const QByteArray, packet.getPacket()));
}
