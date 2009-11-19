#include "DataManagerServer.h"
#include "../Common/DataPlugin.h"
#include "../Common/CommData.h"
#include "../Common/Data.h"

#include "ClientSocket.h"
#include "PluginManagerServer.h"

#include <QHash>
#include <QMetaObject>

void DataManagerServer::dataStatusChange(Data* data, quint8 newStatus)
{
	QMutexLocker M(&data->mutex);

	UserData* user = PluginManagerServer::instance()->currentUser();
	quint8 error = 0;
    quint8 oldStatus = data->status();

	// if a client whant an update of a data
	if ((oldStatus == Data::EMPTY || oldStatus == Data::UPTODATE) &&
		 newStatus == Data::UPDATING)
	{
		if (oldStatus == Data::EMPTY)
		{
			if ((error = data->serverRead()))
				return sendData(user, data, Data::DATA_ERROR, error);
			data->_status = Data::UPTODATE;
		}

		return sendData(user, data);
	}

	// if a client save a new value of the data
	if ((oldStatus == Data::EMPTY || oldStatus == Data::UPTODATE) &&
		 newStatus == Data::SAVING)
	{
		if (oldStatus == Data::EMPTY)
		{
			if ((error = data->serverRead()))
				return sendData(user, data, Data::DATA_ERROR, error);
			data->_status = Data::UPTODATE;
		}

		if ((error = data->serverSave()))
			return sendData(user, data, Data::DATA_ERROR, error);

		data->_status = Data::UPTODATE;

		//send to the user who saved the data SAVED
		sendData(user, data, Data::SAVED);

		//send to the other user the data UPTODATE
		foreach (UserData* u, ClientSocket::connectedUsers.keys())
			if (u != user)
				sendData(u, data);

		return;
	}

	// if a client want to create a new data
	if (oldStatus == Data::EMPTY &&
		newStatus == Data::CREATING)
	{
		QByteArray oldKey;
		QDataStream stream(&oldKey, QIODevice::ReadWrite);
		data->keyToStream(stream);

		if ((error = data->serverCreate()))
			return sendData(user, data, Data::DATA_ERROR, error);
		data->_status = Data::UPTODATE;

		//send to the user who saved the data CREATED
		sendData(user, data, Data::CREATED, 0, oldKey);

		//send to the other user the data UPTODATE
		foreach (UserData* u, ClientSocket::connectedUsers.keys())
			if (u != user)
				sendData(u, data);

		return;
	}

	// if a client delete a data
	if ((oldStatus == Data::EMPTY || oldStatus == Data::UPTODATE) &&
		 newStatus == Data::DELETING)
	{
		if ((error = data->serverRemove()))
			return sendData(user, data, Data::DATA_ERROR, error);
		data->_status = Data::DELETED;

		//send to every users the data DELETED
		foreach (UserData* u, ClientSocket::connectedUsers.keys())
			sendData(u, data, Data::DELETED);

		//TODO: test with this 2 lines
		//		M.unlock();
		//		delete data;
		return;
	}

	qDebug() << "Data" << data << "change status from" << (Data::DataStatus)oldStatus << "to" << (Data::DataStatus)newStatus << "which is not authorized.";
}

void DataManagerServer::receiveData(UserData* user, const QByteArray& d)
{
    QDataStream stream(d); // ReadOnly
	quint8      status;    
	stream  >>  status;

	if (status != Data::UPDATING && status != Data::DELETING && status != Data::CREATING && status != Data::SAVING)
	{
		qWarning() << "DataManagerServer received a data with status" << status << "which is not authorized.";
		return;
	}

	Data* data = plugin->dataWithKey(stream);
	QMutexLocker(&data->mutex);
	qDebug() << "lock" << data;

	if ( ! data->canAccess(user))
	{
		qWarning() << "User" << user->login() << "try to access to a data" << data << "without authorization.";
		return;
	}

	if (status == Data::UPDATING)
	{
		data->setStatus(Data::UPDATING);
		return;
	}

	if ( ! data->canChange(user))
	{
		if (status == Data::CREATING)
			qWarning() << "User" << user->login() << "try to create a data" << data << "without authorization.";
		else if (status == Data::SAVING)
			qWarning() << "User" << user->login() << "try to save a data" << data << "without authorization.";
		else if (status == Data::DELETING)
			qWarning() << "User" << user->login() << "try to delete a data" << data << "without authorization.";
		return;
	}

	if (status != Data::DELETING)
		data->dataFromStream(stream);

	data->setStatus(status);
}

void DataManagerServer::sendData(UserData* user, Data* data) const
{
	sendData(user, data, Data::UPDATED);
}

void DataManagerServer::sendData( UserData* user, Data* data, quint8 status, quint8 error, const QByteArray& oldKey) const
{
	QMutexLocker(&data->mutex);
	CommData packet(plugin->dataType());
    QDataStream stream(&packet.data, QIODevice::WriteOnly);

	if (status != Data::UPDATED &&
		status != Data::SAVED &&
		status != Data::CREATED &&
		status != Data::DELETED &&
		status != Data::DATA_ERROR)
	{
		qWarning() << "DataManagerServer try to send a data with status" << (Data::DataStatus)status << "which is not authorized.";
		return;
	}

	stream << status;

	if (status == Data::CREATED)
		stream << oldKey;

	data->keyToStream(stream);

	if (status == Data::UPDATED)
		data->dataToStream(stream);

	else if (status == Data::DATA_ERROR)
	{
		stream << error;
		stream << data->status();
		if (data->status() == Data::UPTODATE)
			data->dataToStream(stream);
	}

	ClientSocket* socket = ClientSocket::connectedUsers.value(user);
    if (socket)
       QMetaObject::invokeMethod(socket, "sendPacket", Qt::QueuedConnection, Q_ARG(QByteArray, packet.getPacket()));
    else
        qWarning() << "DataManagerServer::sendData: user not connected";
}
