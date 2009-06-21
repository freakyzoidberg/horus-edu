#ifndef DATAPLUGIN_H
#define DATAPLUGIN_H

#ifdef HORUS_SERVER
#include <QtSql>
#endif

#include "QByteArray"
#include "Plugin.h"
#include "Data.h"

class UserData;

//! this object have to references these own data in memory (if needed) and to provide an interface to the other plugins to access these
/*!
 * run in the data thread
 */
class DataPlugin : public Plugin
{
  Q_OBJECT

public:
    virtual const QString getDataType() const = 0;

protected:
    //! Return the pointer to the Data with a his unique key read in the stream
    virtual Data*         getDataWithKey(QDataStream&) = 0;
#ifdef HORUS_CLIENT
    //! On the client, when creating a new data, the key can change. So this function have to update the data with the new key in the stream
    virtual void          dataHaveNewKey(Data*, QDataStream&) = 0;
#else
#ifdef HORUS_SERVER
    //! On the server, the module may want to che if the database is ok
    virtual bool          verifyDataBase(QSqlQuery&) = 0;
#else
#error "You must define HORUS_CLIENT or HORUS_SERVER in your project."
#endif
#endif
public:
    //! Called by the data when its status change.
    /*!
     *  Have differents implementation on the Client and the Server.
     *  Can be overloaded if:
     *  - More status are supported (ex: a file can be [up/down]loading)
     *  - To check permitions (also on the client side but can be less restrictive)
     */
    void                  dataStatusChange(UserData* user, Data* data, Data::DataStatus oldStatus);

public slots:
    void                  receiveData(UserData* user, const QByteArray& packet);
signals:
    void                  sendData(UserData* user, const QByteArray& packet);
};

#endif // DATAPLUGIN_H
