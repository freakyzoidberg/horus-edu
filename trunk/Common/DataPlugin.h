#ifndef DATAPLUGIN_H
#define DATAPLUGIN_H

#include "QByteArray"
#include "Plugin.h"
#include "MetaPlugin.h"

class Data;
class UserData;
class DataManager;

//! this object have to references these own data in memory (if needed) and to provide an interface to the other plugins to access these
/*!
 * run in the data thread
 */
class DataPlugin : public Plugin
{
  Q_OBJECT
  Q_INTERFACES(Plugin)
	friend class MetaPlugin;
	friend class DataManagerClient;

public:
	virtual const QString		getDataType() const = 0;

    //! Return the pointer to the Data with a his unique key read in the stream
	virtual Data*				getDataWithKey(QDataStream&) = 0;
	//! called by the UserCache to put every data into the cache
	virtual inline QList<Data*>	allDatas() const { return QList<Data*>(); }

#ifdef HORUS_CLIENT
    //! On the client, when creating a new data, the key can change. So this function have to update the data with the new key in the stream
	virtual inline void			dataHaveNewKey(Data*, QDataStream&) {}
#endif
#ifdef HORUS_SERVER
    //! On the server, the module may want to check if the database is ok
	virtual inline void			loadData() { }
	virtual inline void			userConnected(UserData*, QDateTime) { }
#endif

	DataManager*				dataManager;

signals:
	void						dataCreated(Data* data);
	void						dataUpdated(Data* data);
	void						dataRemoved(Data* data);
	void						dataError  (Data* data, quint8 error);

protected:
	inline						DataPlugin() {}
	inline						~DataPlugin() {}
};

#ifdef HORUS_SERVER
typedef DataPlugin ServerDataPlugin;
Q_DECLARE_INTERFACE(ServerDataPlugin, "net.horus.ServerDataPlugin/1.0");
#endif
#ifdef HORUS_CLIENT
typedef DataPlugin ClientDataPlugin;
Q_DECLARE_INTERFACE(ClientDataPlugin, "net.horus.ClientDataPlugin/1.0");
#endif

#endif // DATAPLUGIN_H
