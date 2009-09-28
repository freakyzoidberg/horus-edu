#ifndef MAILDATAPLUGIN_H
#define MAILDATAPLUGIN_H

#include <QHash>
#include "../../DataPlugin.h"

class Data;
class TreeData;
class MailData;
class MailDataPlugin : public DataPlugin
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerDataPlugin)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientDataPlugin)
#endif

public:
        inline const QString pluginName()    const { return "Mail Data Plugin"; }
	inline const QString pluginVersion() const { return "0.1"; }
        inline const QString getDataType()   const { return "MailData"; }

       // MailData*      getMail(TreeData* node);
       // MailData*      getMail(quint32 nodeId);
#ifdef HORUS_CLIENT
    void                 dataHaveNewKey(Data*d, QDataStream& s);
#endif
#ifdef HORUS_SERVER
    void                 loadDataBase(QSqlQuery&);
    void                 userDisconnected(UserData* user);
    UserData*            authenticatePassword(QSqlQuery& query, const QString& login, const QByteArray& password);
    UserData*            authenticateSession (QSqlQuery& query, const QString& login, const QByteArray& sesion);
    void                 sendUpdates(QSqlQuery&, UserData* user, QDateTime date);
#endif

private:
    //! Return the pointer to the Data with a his unique key read in the stream
    Data*                getDataWithKey(QDataStream& s);


        QList<MailData*> Mails;
};

#endif // MAILDATAPLUGIN_H
