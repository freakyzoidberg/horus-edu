#ifndef DATAPLUGIN_H
#define DATAPLUGIN_H

#include "Defines.h"

#ifdef HORUS_SERVER
#include <QtSql>
#endif

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

public:
    virtual const QString getDataType() const = 0;

//    virtual inline const QList<Data*> getAllDatas() const { return QList<Data*>(); }

    //! Return the pointer to the Data with a his unique key read in the stream
    virtual Data*         getDataWithKey(QDataStream&) = 0;

#ifdef HORUS_CLIENT
    //! Return a pointer to a new Data with a unique temporary key
    virtual inline Data*         getNewData() { return 0; }

    //! On the client, when creating a new data, the key can change. So this function have to update the data with the new key in the stream
    virtual inline void          dataHaveNewKey(Data*, QDataStream&) {}
#endif
#ifdef HORUS_SERVER
    //! On the server, the module may want to check if the database is ok
    virtual inline void   loadDataBase(QSqlQuery&) { }
    virtual inline void   sendUpdates(QSqlQuery&, UserData*, QDateTime) { }
#endif
    DataManager*          dataManager;

signals:
	void dataUpdated(Data* data);

	friend class MetaPlugin;
protected:
	inline DataPlugin() {}
	inline ~DataPlugin() {}
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
