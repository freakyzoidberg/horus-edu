#ifndef MAILSNETWORK_H
#define MAILSNETWORK_H

#include "../../../NetworkPlugin.h"

class MailsNetwork : public NetworkPlugin
{
    Q_OBJECT

public:
    MailsNetwork();
    const QString       pluginVersion() const {return "0.1";}
    const QString       pluginName() const {return "Mail Network client";}

public slots:
    void receivePacket(const PluginPacket) {}
    void update();


};

#endif // MAILSNETWORK_H
