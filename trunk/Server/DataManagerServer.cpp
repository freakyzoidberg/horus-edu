#include "DataManagerServer.h"
#include "../Common/DataPlugin.h"
#include "../Common/CommData.h"
#include "../Common/Data.h"

#include "Sql.h"
#include "ClientSocket.h"
#include "PluginManagerServer.h"

#include <QHash>
#include <QMetaObject>

void DataManagerServer::dataStatusChange(Data* data, quint8 newStatus) const
{
    Sql conn;
    QSqlQuery query(QSqlDatabase::database(conn));
    QMutexLocker(data->lock);

    quint8 oldStatus = data->status();

	// if a client whant an update of a data
	if ((oldStatus == Data::EMPTY || oldStatus == Data::UPTODATE) &&
		 newStatus == Data::UPDATING)
	{
		if (oldStatus == Data::EMPTY)
		{
			data->fillFromDatabase(query);
			data->_status = Data::UPTODATE;
		}

		sendData(PluginManagerServer::instance()->currentUser(), data);
		return;
	}

	// if a client save a new value of the data
	if ((oldStatus == Data::EMPTY || oldStatus == Data::UPTODATE) &&
		 newStatus == Data::SAVING)
	{
		if (oldStatus == Data::EMPTY)
		{
			data->fillFromDatabase(query);
			data->_status = Data::UPTODATE;
		}

		data->saveIntoDatabase(query);

		//send to the user who saved the data SAVED
		data->_status = Data::SAVED;
		sendData(PluginManagerServer::instance()->currentUser(), data);

		//send to the other user the data UPTODATE
		data->_status = Data::UPTODATE;
		foreach (UserData* u, ClientSocket::connectedUsers.keys())
			if (u != PluginManagerServer::instance()->currentUser())
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

		data->createIntoDatabase(query);

		//send to the user who saved the data CREATED
		data->_status = Data::CREATED;
		sendData(PluginManagerServer::instance()->currentUser(), data, oldKey);

		//send to the other user the data UPTODATE
		data->_status = Data::UPTODATE;
		foreach (UserData* u, ClientSocket::connectedUsers.keys())
			if (u != PluginManagerServer::instance()->currentUser())
				sendData(u, data);

		return;
	}

	// if a client delete a data
	if ((oldStatus == Data::EMPTY || oldStatus == Data::UPTODATE) &&
		 newStatus == Data::DELETING)
	{
		data->deleteFromDatabase(query);
		data->_status = Data::DELETED;

		//send to every users the data DELETED
		foreach (UserData* u, ClientSocket::connectedUsers.keys())
			sendData(u, data);
		return;
	}

	qDebug() << "Data" << data << "change status from" << oldStatus << "to" << newStatus << "which is not authorized.";
}

void DataManagerServer::receiveData(UserData* user, const QByteArray& d) const
{
    QDataStream stream(d); // ReadOnly
	quint8      status;    
	stream  >>  status;

	if (status != Data::UPDATING && status != Data::DELETING && status != Data::CREATING && status != Data::SAVING)
	{
		qWarning() << "DataManagerServer received a data with status" << status << "which is not authorized.";
		return;
	}

	Data* data = plugin->getDataWithKey(stream);
	QMutexLocker(data->lock);

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

void DataManagerServer::sendData(UserData* user, Data* data, const QByteArray oldKey) const
{
    QMutexLocker(data->lock);
	CommData packet(plugin->getDataType());
    QDataStream stream(&packet.data, QIODevice::WriteOnly);
	quint8 status = data->status();

	if (status != Data::UPTODATE && status != Data::SAVED && status != Data::CREATED && status != Data::DELETED)
	{
		qWarning() << "DataManagerServer try to send a data with status" << status << "which is not authorized.";
		return;
	}

	stream << status << data->error();

	if (status == Data::CREATED)
		stream << oldKey;

	data->keyToStream(stream);
	if (status == Data::UPTODATE && ! data->error())
		data->dataToStream(stream);

	ClientSocket* socket = ClientSocket::connectedUsers.value(user);
    if (socket)
       QMetaObject::invokeMethod(socket, "sendPacket", Qt::QueuedConnection, Q_ARG(QByteArray, packet.getPacket()));
    else
        qWarning() << "DataManagerServer::sendData: user not connected";
}
