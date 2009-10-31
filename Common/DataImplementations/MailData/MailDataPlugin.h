#ifndef MAILDATAPLUGIN_H
#define MAILDATAPLUGIN_H

#include <QHash>
#include "../../DataPlugin.h"
#ifdef HORUS_SERVER
#include "../../../Server/Plugins/MailServer/Implementation/mail.h"
#endif

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
        inline const QString pluginName()    const { return "MailDataPlugin"; }
	inline const QString pluginVersion() const { return "0.1"; }
        inline const QString getDataType()   const { return "MailData"; }


        MailData*      getMail(quint32 i);
#ifdef HORUS_CLIENT
    void                 dataHaveNewKey(Data*d, QDataStream& s);
#endif
#ifdef HORUS_SERVER
		QList<Data*>			datasForUpdate(UserData* user, QDateTime date);

public slots:
        void SendMailToClient(Mail*);

#endif
private:
    //! Return the pointer to the Data with a his unique key read in the stream
    Data*                getDataWithKey(QDataStream& s);


        QList<MailData*> Mails;

        public:
        MailData* createMail();
};

#endif // MAILDATAPLUGIN_H
