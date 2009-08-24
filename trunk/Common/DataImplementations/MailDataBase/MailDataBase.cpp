#include "MailDataBase.h"
#include "MailDataBasePlugin.h"
#include "MailSender.h"
MailDataBase::MailDataBase(MailDataBasePlugin* plugin, QString part, quint8 scope, quint32 ownerId)
        : MailData((MailDataPlugin*)plugin)
{

    _part = part;
    _scope = scope;
    _owner = ownerId;
#ifdef HORUS_SERVER
    inDatabase = false;
#endif
}

void MailDataBase::keyToStream(QDataStream& s)
{
    s << _part
      << _scope
      << _owner;
}

void MailDataBase::dataToStream(QDataStream& s)
{
    s << _values;
}

void MailDataBase::dataFromStream(QDataStream& s)
{
    s >> _values;
}

QDebug MailDataBase::operator<<(QDebug debug) const
{
    return debug << _part
                 << _scope
                 << _owner
                 << _values;
}

#ifdef HORUS_SERVER
void MailDataBase::fillFromDatabase(QSqlQuery& query)
{
    query.prepare("SELECT value FROM settings WHERE user=? AND plugin=? AND scope=?;");
    query.addBindValue(_owner);
    query.addBindValue(_part);
    query.addBindValue(_scope);
    if ( ! query.exec() || ! query.next())
    {
//        _error = NOT_FOUND;
        _values = QVariantHash();
        return;
    }
    inDatabase = true;
    _values = query.value(0).toHash();
}

void MailDataBase::createIntoDatabase(QSqlQuery& query)
{
    query.prepare("INSERT INTO settings (user,plugin,scope,value) VALUES (?,?,?,?);");
    query.addBindValue(_owner);
    query.addBindValue(_part);
    query.addBindValue(_scope);
    query.addBindValue(_values);
    if ( ! query.exec() || ! query.next())
    {
        _error = DATABASE_ERROR;
        return;
    }
}

void MailDataBase::saveIntoDatabase  (QSqlQuery& query)
{
    if ( ! inDatabase)
        return createIntoDatabase(query);

    query.prepare("UPDATE settings SET value=? WHERE user=? AND plugin=? AND scope=?;");
    query.addBindValue(_values);
    query.addBindValue(_owner);
    query.addBindValue(_part);
    query.addBindValue(_scope);
    if ( ! query.exec() || ! query.next())
    {
        _error = NOT_FOUND;
        return;
    }
}

void MailDataBase::deleteFromDatabase(QSqlQuery& query)
{
    query.prepare("DELETE FROM settings WHERE user=? AND plugin=? AND scope=?;");
    query.addBindValue(_owner);
    query.addBindValue(_part);
    query.addBindValue(_scope);
    if ( ! query.exec() || ! query.next())
    {
        _error = NOT_FOUND;
        return;
    }
}
#endif

bool MailDataBase::sendmail(QString host, quint32 port, QString login, QString pass, QString sender, QString dest, QString subject, QString content)
{
    QStringList mylist;
    mylist.append(dest);
     MailSender *test1 = new MailSender(host, sender,mylist , subject, content);
                test1->setPriority(MailSender::high);
                test1->send();
                delete test1;
    return true;
}
