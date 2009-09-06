#include "Administration.h"

QWidget             *Administration::getWidget()
{
    return (this->widget);
}

void Administration::receivePacket(UserData* user, const PluginPacket& packet)
{
    //this->widget->packetManager(packet.data.toHash());
}

const QString   Administration::pluginName() const
{
    return ("Administration");
}

const QString   Administration::pluginVersion() const
{
    return ("1.1");
}

void Administration::load()
{
        this->widget = new AdminMainFrame();
        //connect(this->widget, SIGNAL(send(PluginPacket *packet)), this, SLOT(send(PluginPacket *packet)));
        load();
}

void Administration::unload()
{
	delete this->widget;
        unload();
}

void Administration::send(PluginPacket *packet)
{
	emit sendPacket(*packet);
}
