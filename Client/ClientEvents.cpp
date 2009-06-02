#include "ClientEvents.h"

QEvent::Type ClientEvents::StartEvent = (QEvent::Type)QEvent::registerEventType();
QEvent::Type ClientEvents::StopEvent = (QEvent::Type)QEvent::registerEventType();
QEvent::Type ClientEvents::NetworkReceiveEvent = (QEvent::Type)QEvent::registerEventType();
QEvent::Type ClientEvents::UnloadPluginEvent = (QEvent::Type)QEvent::registerEventType();
QEvent::Type ClientEvents::LoadPluginEvent = (QEvent::Type)QEvent::registerEventType();
QEvent::Type ClientEvents::SendPacketEvent = (QEvent::Type)QEvent::registerEventType();
QEvent::Type ClientEvents::RecvPacketEvent = (QEvent::Type)QEvent::registerEventType();
QEvent::Type ClientEvents::ShowLoginEvent = (QEvent::Type)QEvent::registerEventType();
QEvent::Type ClientEvents::HideLoginEvent = (QEvent::Type)QEvent::registerEventType();
QEvent::Type ClientEvents::SendLoginEvent = (QEvent::Type)QEvent::registerEventType();
QEvent::Type ClientEvents::PluginEvent = (QEvent::Type)QEvent::registerEventType();
QEvent::Type ClientEvents::OfflineModeEvent = (QEvent::Type)QEvent::registerEventType();

SendPacketEvent::SendPacketEvent(const QByteArray p) : QEvent(ClientEvents::SendPacketEvent)
{
    pack = p;
}

SendPacketEvent::SendPacketEvent(const SendPacketEvent &s) : QEvent(ClientEvents::SendPacketEvent)
{
    pack = s.pack;
}

RecvPacketEvent::RecvPacketEvent(const QByteArray p) : QEvent(ClientEvents::RecvPacketEvent)
{
    pack = p;
}

SendLoginEvent::SendLoginEvent(const QByteArray p) : QEvent(ClientEvents::SendLoginEvent)
{
    pack = p;
}

SendLoginEvent::SendLoginEvent(const SendLoginEvent &s) : QEvent(ClientEvents::SendLoginEvent)
{
    pack = s.pack;
}

PluginEvent::PluginEvent(const PluginPacket p) : QEvent(ClientEvents::PluginEvent)
{
    pack = p;
}

PluginEvent::PluginEvent(const PluginEvent &s) : QEvent(ClientEvents::PluginEvent)
{
    pack = s.pack;
}
