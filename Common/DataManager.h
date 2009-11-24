#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QByteArray>

class Data;
class UserData;

class DataManager : public QObject
{
	Q_OBJECT
public slots:
	virtual void dataStatusChange(Data* data, quint8 newStatus) = 0;
#ifdef HORUS_CLIENT
	virtual void sendData(Data* data) = 0;
	virtual void receiveData(const QByteArray& data) = 0;
#endif
#ifdef HORUS_SERVER
	virtual void sendData(UserData* user, Data* data) = 0;
	virtual void receiveData(UserData* user, const QByteArray& data) = 0;
#endif
};

#endif // DATAMANAGER_H
