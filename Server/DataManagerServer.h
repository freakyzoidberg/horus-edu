#ifndef DATAMANAGERSERVER_H
#define DATAMANAGERSERVER_H

#include "../Common/DataManager.h"

class DataPlugin;
class DataManagerServer : public DataManager
{
	Q_OBJECT
public:
     inline DataManagerServer(DataPlugin* _plugin) : DataManager(_plugin) { plugin=_plugin; }

	 // DataManager Interface
    //! Called by the data when its status change.
    /*!
     *  Have differents implementation on the Client and the Server.
     *  Can be overloaded if:
     *  - More status are supported (ex: a file can be [up/down]loading)
     *  - To check permitions (also on the client side but can be less restrictive)
     */
	void			dataStatusChange(Data* data, quint8 newStatus) const;
	inline void		sendData(UserData* user, Data* data) const { sendData(user, data, QByteArray()); }

public slots:
	void			receiveData(UserData *, const QByteArray& packet) const;


private:
	//! Send a "data" to a "user"
	/*!
	 * \param oldkey: contain the temporary key when the client is creating a data (internal use only)
	 */
	void			sendData(UserData* user, Data* data, const QByteArray oldKey) const;

	DataPlugin*		plugin;
};

#endif // DATAMANAGERSERVER_H
