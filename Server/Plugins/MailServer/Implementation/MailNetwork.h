#ifndef MAILNETWORK_H
#define MAILNETWORK_H

#include "../../../NetworkPlugin.h"

class MailNetwork : public NetworkPlugin
{

Q_OBJECT
Q_INTERFACES(NetworkPluginServer)

public:
    MailNetwork();

	//Plugin
	inline const QString   pluginName()    const { return "Mail Network"; }
	inline const QString   pluginVersion() const { return "1"; }


	//NetworkPlugin
	void receivePacket(UserData* user, const PluginPacket);
};

#endif // MAILNETWORK_H
