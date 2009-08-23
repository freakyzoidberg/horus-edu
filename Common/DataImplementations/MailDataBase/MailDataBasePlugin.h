#ifndef MAILDATABASEPLUGIN_H
#define MAILDATABASEPLUGIN_H

#include <QHash>
#include "../../MailDataPlugin.h"

class Data;
class MailData;
class MailDataBase;
class MailDataBasePlugin : public MailDataPlugin
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerMailDataPlugin)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientMailDataPlugin)
#endif

public:
    MailDataBasePlugin();
    inline const QString pluginName() const { return "Mail Data Base"; }
    inline const QString pluginVersion() const { return "0.1"; }

    inline const QString getDataType() const { return "Mail"; }

    /*
    MailData*        getSettings(QString part = QString(), quint8 scope = 0, quint32 userId = 0);
*/
#ifdef HORUS_SERVER
    bool                 verifyDataBase(QSqlQuery&);
#endif

protected:
    //! Return the pointer to the Data with a his unique key read in the stream
    Data*                getDataWithKey(QDataStream& s);

private:
    QList<MailData*> settings;
};

#endif // MAILDATABASEPLUGIN_H
