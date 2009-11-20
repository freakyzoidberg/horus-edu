#ifndef DATAPLUGIN_H
#define DATAPLUGIN_H

#include "QByteArray"
#include "Plugin.h"
#include "MetaPlugin.h"

#ifdef HORUS_CLIENT
#include <QAbstractItemModel>
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
	friend class DataManagerClient;

public:
	DataManager*				dataManager;

	virtual const QString		dataType() const = 0;

    //! Return the pointer to the Data with a his unique key read in the stream
	virtual Data*				dataWithKey(QDataStream&) = 0;
	//! called by the UserCache to put every data into the cache
	virtual inline QList<Data*>	allDatas() const { return QList<Data*>(); }

#ifdef HORUS_CLIENT
public:
	//! On the client, when creating a new data, the key can change. So this function have to update the data with the new key in the stream
	virtual inline void			dataHaveNewKey(Data*, QDataStream&) {}
	inline QAbstractItemModel*	model() { return _model; }
protected:
	QAbstractItemModel*			_model;
#endif
#ifdef HORUS_SERVER
public:
	//! On the server, the module may want to check if the database is ok
	virtual inline void			loadData() { }
	virtual inline QList<Data*>	datasForUpdate(UserData*, QDateTime) { return QList<Data*>(); }
#endif

signals:
	void						dataCreated(Data* data);
	void						dataUpdated(Data* data);
	void						dataRemoved(Data* data);
	void						dataError  (Data* data, quint8 error);
	void						dataStatusChanged(Data* data);

protected:
	inline						DataPlugin() {
#ifdef HORUS_CLIENT
		_model=0;
#endif
	}
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
