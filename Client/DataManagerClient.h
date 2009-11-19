#ifndef DATAMANAGERCLIENT_H
#define DATAMANAGERCLIENT_H

#include "../Common/DataManager.h"
#include <QMetaType>

class DataPlugin;
class DataManagerClient : public DataManager
{
  Q_OBJECT
public:
	inline DataManagerClient(DataPlugin* parent) { plugin = parent; qRegisterMetaType<Data*>("Data*"); }

public slots:
	//! Called by the data when its status change.
    /*!
     *  Have differents implementation on the Client and the Server.
     *  Can be overloaded if:
     *  - More status are supported (ex: a file can be [up/down]loading)
     *  - To check permitions (also on the client side but can be less restrictive)
     */
	void dataStatusChange(Data* data, quint8 newStatus);
	void sendData(UserData*, Data* data) const;
	void receiveData(UserData*, const QByteArray& packet);

private:
	void sendData(UserData*, const QByteArray& packet) const;
	DataPlugin* plugin;
	QList<Data*>	_needSaveAgain;
};

#endif // DATAMANAGERCLIENT_H
