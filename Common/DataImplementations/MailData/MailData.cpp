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
quint8 MailData::serverSave()
{
    QString host = QSettings().value("MAIL/MAIL_HOSTNAME", ".").toString();
    qDebug() << host;
    QString domain = QSettings().value("MAIL/MAIL_DOMAIN", ".").toString();
    qDebug() << domain;
    QString port = QSettings().value("MAIL/MAIL_PORT", ".").toString();
    qDebug() << port;
//    qDebug() << QVariant(port).toInt();

    QString qssl = QSettings().value("MAIL/MAIL_SSLTLS", ".").toString();
    QString qlogin = QSettings().value("MAIL/MAIL_LOGIN", ".").toString();

     smtp *test1 = new smtp(host, _plugin->pluginManager->currentUser()->login()+"@"+domain,this->_to , this->_subject, this->_content);




     if (_cc.count() > 0)
         test1->setCc(_cc);
     if (_bcc.count() > 0)
         test1->setBcc(_bcc);
                test1->setPriority(smtp::high);
                //test1->setSmtpServer("localhost");
                //test1->setLogin("login", "pass");
                test1->setPort(QVariant(port).toInt());
                //test1->setSsl(true);
                test1->send();
                qDebug() << test1->lastError();
                delete test1;
	return NONE;
}
#endif
