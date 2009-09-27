#ifndef MAILSERVERPLUGIN_H
#define MAILSERVERPLUGIN_H

#include "../../../NetworkPlugin.h"

class UserData;
class MailServerPlugin : public NetworkPlugin
{
    Q_OBJECT
    Q_INTERFACES(NetworkPluginServer Plugin)

    // Plugin Interface
public:
    inline const QString   pluginName()    const { return "MailServerPlugin"; }
    inline const QString   pluginVersion() const { return "0.1"; }

    // NetworkPlugin Interface
public slots:
    void receivePacket(UserData* user, const PluginPacket);
private :
   bool            sendmail(QString host, quint32 port, QString login, QString pass, QString sender, QString dest, QString subject, QString content);
};

#endif // MAILSERVERPLUGIN_H
