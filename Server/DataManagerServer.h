#ifndef DATAMANAGERSERVER_H
#define DATAMANAGERSERVER_H

#include "../Common/DataManager.h"
class DataPlugin;

class DataManagerServer : public DataManager
{
	Q_OBJECT
public:
	DataManagerServer(DataPlugin* _plugin);

	//DataManager
public slots:
	void			dataStatusChange(Data* data, quint8 newStatus);
	void			sendData(UserData* user, Data* data);
	void			receiveData(UserData *, const QByteArray& packet);


private:
	void			sendData(UserData* user, Data* data, quint8 status, quint8 error = 0, const QByteArray& olgKey="");
	DataPlugin*		_plugin;
};

#endif // DATAMANAGERSERVER_H
