/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "DataManagerClient.h"

#include <QMetaType>
#include <QDebug>

#include "../Common/CommData.h"
#include "../Common/UserData.h"

#include "PluginManagerClient.h"

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
	if (newStatus == Data::REMOVING && oldStatus == Data::REMOVING)
		return;

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
	//quint8 oldStatus = data->_status;

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

	QList<Data*> list = _dependantDatas.values(data);
	_dependantDatas.remove(data);
	foreach (Data* dep, list)
		sendData(dep);
}

void DataManagerClient::sendData(Data* data)
{
	QMutexLocker(&data->mutex);
	if (data->status() == Data::SAVING || data->status() == Data::CREATING)
		foreach (Data* dep, data->dependsOfCreatedData())
			if (dep && dep != data && (dep->status() == Data::EMPTY || dep->status() == Data::CREATING))
			{
				qDebug() << data << "is waiting dependance" << dep << "being created";
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
