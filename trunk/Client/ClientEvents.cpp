#include "ClientEvents.h"

QEvent::Type ClientEvents::StartEvent = (QEvent::Type)QEvent::registerEventType();
QEvent::Type ClientEvents::StopEvent = (QEvent::Type)QEvent::registerEventType();
QEvent::Type ClientEvents::NetworkReceiveEvent = (QEvent::Type)QEvent::registerEventType();
QEvent::Type ClientEvents::UnloadPluginEvent = (QEvent::Type)QEvent::registerEventType();
QEvent::Type ClientEvents::LoadPluginEvent = (QEvent::Type)QEvent::registerEventType();
QEvent::Type ClientEvents::SendPacketEvent = (QEvent::Type)QEvent::registerEventType();
QEvent::Type ClientEvents::RecvPacketEvent = (QEvent::Type)QEvent::registerEventType();

SendPacketEvent::SendPacketEvent(const QByteArray p) : QEvent(ClientEvents::SendPacketEvent)
{
    pack = p;
}

RecvPacketEvent::RecvPacketEvent(const QByteArray p) : QEvent(ClientEvents::RecvPacketEvent)
{
    pack = p;
}
