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
#include "DataManagerServer.h"
#include "../Common/DataPlugin.h"
#include "../Common/CommData.h"
#include "../Common/Data.h"

#include "ClientSocket.h"
#include "PluginManagerServer.h"

#include <QMetaObject>
#include <QMetaType>

DataManagerServer::DataManagerServer(DataPlugin* plugin)
{
	_plugin = plugin;
	qRegisterMetaType<Data*>("Data*");
}

void DataManagerServer::dataStatusChange(Data* data, quint8 newStatus)
{
	QMutexLocker M(&data->mutex);
	UserData* user = PluginManagerServer::instance()->currentUser();
	quint8 error = 0;

	// if a client want to create a new data
	if (data->_status == Data::EMPTY && newStatus == Data::CREATING)
	{
		QByteArray oldKey;
		QDataStream stream(&oldKey, QIODevice::ReadWrite);
		// save the temporary key
		data->keyToStream(stream);

		if ((error = data->serverCreate()))
			return sendData(user, data, Data::DATA_ERROR, error);
		data->_status = Data::UPTODATE;
		emit _plugin->dataCreated(data);
		emit data->statusChanged();
		emit _plugin->dataStatusChanged(data);

		//send to the user who saved, the data CREATED
		sendData(user, data, Data::CREATED, 0, oldKey);
		//send to the other user the data UPDATED
		foreach (UserData* u, ClientSocket::connectedUsers.keys())
			if (u != user && data->canAccess(u))
				sendData(u, data);
		return;
	}

	if (data->_status != Data::UPTODATE && data->_status != Data::EMPTY)
	{
		qDebug() << "Should not happen:" << data << "status change from" << (Data::Status)data->_status << "to" << (Data::Status)newStatus << "nothing done.";
		return;
	}

	// if a client save a new value of the data
	if (newStatus == Data::SAVING)
	{
		if ((error = data->serverSave()))
			return sendData(user, data, Data::DATA_ERROR, error);
		data->_status = Data::UPTODATE;
		emit data->statusChanged();
		emit _plugin->dataStatusChanged(data);

		//send to the user who saved the data SAVED
		sendData(user, data, Data::SAVED);
		//send to the other user the data UPDATED
		foreach (UserData* u, ClientSocket::connectedUsers.keys())
			if (u != user && data->canAccess(u))
				sendData(u, data);
		return;
	}

	// if a client delete a data
	if (newStatus == Data::REMOVING)
	{
		if ((error = data->serverRemove()))
			return sendData(user, data, Data::DATA_ERROR, error);
		data->_status = Data::REMOVED;
		emit data->removed();
		emit _plugin->dataRemoved(data);
		emit data->statusChanged();
		emit _plugin->dataStatusChanged(data);

		//send to every users the data DELETED
		foreach (UserData* u, ClientSocket::connectedUsers.keys())
			if (data->canAccess(u))
				sendData(u, data);
		//TODO: save every DELETED data somewhere, to be able to say to not-connected clients witch data is removed
		return;
	}

	qDebug() << "Should not happen:" << data << "status change from" << (Data::Status)data->_status << "to" << (Data::Status)newStatus << "nothing done.";
}

void DataManagerServer::receiveData(UserData* user, const QByteArray& d)
{
    QDataStream stream(d); // ReadOnly
	quint8      status;    
	stream  >>  status;
	Data* data = _plugin->dataWithKey(stream);
	QMutexLocker(&data->mutex);

	if (status != Data::REMOVING && status != Data::CREATING && status != Data::SAVING)
	{
		qDebug() << "Should not happen:" << data << "received status" << (Data::Status)data->_status << "nothing done.";
		return;
	}

	if ( ! data->canAccess(user))
	{
		qWarning() << user->login() << "try to access to" << data << "without permitions.";
		return;
	}

	if ( ! data->canChange(user))
	{
		if (status == Data::CREATING)
			qWarning() << user->login() << "try to create" << data << "without permitions.";
		else if (status == Data::SAVING)
			qWarning() << user->login() << "try to save"   << data << "without permitions.";
		else if (status == Data::REMOVING)
			qWarning() << user->login() << "try to delete" << data << "without permitions.";
		return;
	}

	if (status != Data::REMOVING)
		data->dataFromStream(stream);

	dataStatusChange(data, status);
}

void DataManagerServer::sendData(UserData* user, Data* data)
{
	sendData(user, data, data->_status);
}

void DataManagerServer::sendData(UserData* user, Data* data, quint8 status, quint8 error, const QByteArray& oldKey)
{
	if ( ! user)
	{
		qDebug() << "Can be normal: invalid user to send the data";
		return;
	}

	//if status UPTODATE, send UPDATED to the client
	if (status == Data::UPTODATE)
		status = Data::UPDATED;

	if (status == Data::EMPTY)
		status = Data::REMOVED;

	QMutexLocker(&data->mutex);
	CommData packet(_plugin->dataType());
    QDataStream stream(&packet.data, QIODevice::WriteOnly);

	if (status != Data::UPDATED &&
		status != Data::SAVED &&
		status != Data::CREATED &&
		status != Data::REMOVED &&
		status != Data::DATA_ERROR)
	{
		qDebug() << "Should not happen:" << data << "is send with status" << (Data::Status)status << "nothing done.";
		return;
	}

	stream << status;

	if (status == Data::CREATED)
		stream << oldKey;

	data->keyToStream(stream);
	stream << data->lastChange();

	if (status == Data::UPDATED)
		data->dataToStream(stream);

	else if (status == Data::DATA_ERROR)
	{
		stream << error;
		stream << data->status();
		if (data->status() == Data::UPTODATE)
			//send the current value if UPTODATE
			data->dataToStream(stream);
	}

	ClientSocket* socket = ClientSocket::connectedUsers.value(user);
	if ( ! socket)
		qDebug() << "Should not happen:" << data << "is send to" << user << "which is not connected.";

	QMetaObject::invokeMethod(socket, "sendPacket", Qt::QueuedConnection, Q_ARG(QByteArray, packet.getPacket()));
}
