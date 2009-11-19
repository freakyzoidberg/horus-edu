#ifndef DATAMANAGERSERVER_H
#define DATAMANAGERSERVER_H

#include "../Common/DataManager.h"
#include <QMetaType>

class DataPlugin;
class DataManagerServer : public DataManager
{
	Q_OBJECT
public:
	 inline DataManagerServer(DataPlugin* _plugin) { plugin=_plugin; qRegisterMetaType<Data*>("Data*"); }

	 // DataManager Interface
public slots:
	//! Called by the data when its status change.
    /*!
     *  Have differents implementation on the Client and the Server.
     *  Can be overloaded if:
     *  - More status are supported (ex: a file can be [up/down]loading)
     *  - To check permitions (also on the client side but can be less restrictive)
     */
	void			dataStatusChange(Data* data, quint8 newStatus);
	void			sendData(UserData* user, Data* data) const;
	void			receiveData(UserData *, const QByteArray& packet);


private:
	//! Send a "data" to a "user"
	/*!
	 * \param oldkey: contain the temporary key when the client is creating a data (internal use only)
	 */
	void			sendData( UserData* user, Data* data, quint8 status, quint8 error = 0, const QByteArray& olgKey="") const;

	DataPlugin*		plugin;
};

#endif // DATAMANAGERSERVER_H
