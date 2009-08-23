#ifndef MAILDATABASE_H
#define MAILDATABASE_H

#ifdef HORUS_SERVER
    #include <QtSql>
#endif

#include <QVariant>
#include "../../Defines.h"
#include "../../MailData.h"
#include "MailDataBasePlugin.h"

class MailDataBase : public MailData
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerMailData)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientMailData)
#endif

  friend class MailDataBasePlugin;

private:
    MailDataBase(MailDataBasePlugin* plugin, QString part = QString(), quint8 scope = CLIENT_USER_SCOPE, quint32 ownerId = 0 );
    inline ~MailDataBase() {}

    quint32 userId;
    QString name;
    QString type;


public:
    //INTERFACE Data
    void            keyToStream(QDataStream& s);
    void            dataToStream(QDataStream& s);
    void            dataFromStream(QDataStream& s);

    QDebug          operator<<(QDebug debug) const;

    // INTERFACE SettingsData
    inline QVariant value(const QString& key) const { return _values.value(key); }
    inline void     setValue(const QString& key, const QVariant& val) { _values[key] = val; }
    inline QString  part() const { return _part; }
    inline quint32  owner() const { return _owner; }
    inline quint8   scope() const { return _scope; }

#ifdef HORUS_SERVER
    void            fillFromDatabase  (QSqlQuery&);
    void            createIntoDatabase(QSqlQuery&);
    void            saveIntoDatabase  (QSqlQuery&);
    void            deleteFromDatabase(QSqlQuery&);
    bool            inDatabase;

    bool            connectToPop(QString host, quint32 port, QString login, QString pass);
#endif

private:
    QVariantHash    _values;
    QString         _part;
    quint32         _owner;
    quint8          _scope;
};

#endif // MAILDATABASE_H
