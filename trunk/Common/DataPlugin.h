#ifndef DATAPLUGIN_H
#define DATAPLUGIN_H

#include "QByteArray"
#include "Plugin.h"
#include "MetaPlugin.h"

#ifdef HORUS_CLIENT
class QAbstractListModel;
#endif

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
	friend class Data;
	friend class MetaPlugin;

public:
	//! contains the data manager, filled by the core juste before Plugin::canLoad() call.
	DataManager*						dataManager;

	//! return the type of the data
	virtual const QString				dataType() const = 0;
    //! Return the pointer to the Data with a his unique key read in the stream
	virtual Data*						dataWithKey(QDataStream&) = 0;

	//! called by the UserCache to put every data into the cache
	inline const QList<Data*>&			allDatas() const { return _allDatas; }

#ifdef HORUS_CLIENT
	friend class DataManagerClient;
	friend class PluginManagerClient;
public:
	//! On the client, when creating a new data, the key can change. So this function have to update the data with the new key in the stream
	virtual inline void					dataHaveNewKey(Data*, QDataStream&) {};
	//! return a list model for the data
	virtual inline QAbstractListModel*	listModel() const { return 0; }
#endif
#ifdef HORUS_SERVER
public:
	virtual inline void					userConnected(UserData*) {}
	virtual inline void					userDisconnected(UserData*) {}
#endif

// theses signals are emmited byt the dataManager, so not nessesary to emit them
// the same signals are also emmited on the data itself
signals:
	void								dataCreated      (Data* data);
	void								dataUpdated      (Data* data);
	void								dataRemoved      (Data* data);
	void								dataStatusChanged(Data* data);
	void								dataError        (Data* data, quint8 error);


protected:
	inline DataPlugin() {}
	virtual inline ~DataPlugin() {}
	QList<Data*>						_allDatas;
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
