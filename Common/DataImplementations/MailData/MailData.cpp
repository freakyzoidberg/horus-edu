#include "MailData.h"
#include "MailDataPlugin.h"
#include "../../PluginManager.h"


void MailData::keyToStream(QDataStream& s)
{
        s << _id;
}

void MailData::dataToStream(QDataStream& s) const
{

    s << _id
    << _to
    << _cc
    << _bcc
    << _subject
    << _content;
	Data::dataToStream(s);
}

void MailData::dataFromStream(QDataStream& s)
{
        s >>
        _id >>
        _to >>
        _cc >>
        _bcc >>
        _subject >>
        _content;
	Data::dataFromStream(s);
}

QDebug MailData::operator<<(QDebug debug) const
{
        return debug << tr("MailData::") << _id;

}

#ifdef HORUS_CLIENT

#include <QIcon>
QVariant MailData::data(int column, int role) const
{
    if (role == Qt::DisplayRole)
    {
       // if (column == 0)
        //		return ((TreeData*)parent())->id();
        if (column == 1)
                        return tr("Mail");
    }
//    else if (role == Qt::DecorationRole && column == 0)
//    {
//        return QIcon(":/user.ico");
//    }
    return QVariant();
}

#endif


#ifdef HORUS_SERVER
#include "../../../Server/Plugins/MailServer/Implementation/smtp.h"
void MailData::fillFromDatabase(QSqlQuery& query)
{
//    query.prepare("SELECT login,level,last_login,surname,name,birth_date,picture,address,phone,country,language,id_tree,enabled,mtime FROM users WHERE id=?;");
//    query.addBindValue(_id);
//    if ( ! query.exec() || ! query.next())
//    {
//        _error = NOT_FOUND;
//        return;
//    }
//    _login      = query.value(0).toString();
//    _level      = (UserLevel)(query.value(1).toUInt());
//    _lastLogin  = query.value(2).toDateTime();
//    _surname    = query.value(3).toString();
//    _name       = query.value(4).toString();
//    _birthDate  = query.value(5).toDate();
//    _picture    = query.value(6).toByteArray();
//    _address    = query.value(7).toString();
//    _phone      = query.value(8).toString();
//    _country    = query.value(9).toString();
//    _language   = query.value(10).toString();
//    TreeDataPlugin* treePlugin = _plugin->pluginManager->findPlugin<TreeDataPlugin*>();
//    if (treePlugin)
//        _node = treePlugin->getNode( query.value(11).toUInt() );
//    else
//        _node = 0;
//    _enabled    = query.value(12).toBool();
//    _lastChange= query.value(13).toDateTime();
}

void MailData::createIntoDatabase(QSqlQuery& query)
{

}

void MailData::saveIntoDatabase(QSqlQuery& query)
{
     smtp *test1 = new smtp("smtp.free.fr", _plugin->pluginManager->currentUser()->login()+"@horus-edu.net",this->_to , this->_subject, this->_content);

     if (_cc.count() > 0)
         test1->setCc(_cc);
         test1->setBcc(_bcc);
                test1->setPriority(smtp::high);
                test1->setSmtpServer("localhost");
                //test1->setLogin("login", "pass");
                //test1->setPort(25);
                //test1->setSsl(true);
                test1->send();
                qDebug() << test1->lastError();
                delete test1;

}

void MailData::deleteFromDatabase(QSqlQuery& query)
{
//    query.prepare("DELETE FROM users WHERE id=?;");
//    query.addBindValue(_id);
//    if ( ! query.exec() || ! query.next())
//    {
//        _error = NOT_FOUND;
//        return;
//    }
}
#endif
