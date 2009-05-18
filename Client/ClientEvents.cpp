#include "ClientEvents.h"

QEvent::Type ClientEvents::StartEvent = (QEvent::Type)QEvent::registerEventType();
QEvent::Type ClientEvents::StopEvent = (QEvent::Type)QEvent::registerEventType();
QEvent::Type ClientEvents::NetworkReceiveEvent = (QEvent::Type)QEvent::registerEventType();
QEvent::Type ClientEvents::UnloadPluginEvent = (QEvent::Type)QEvent::registerEventType();
QEvent::Type ClientEvents::LoadPluginEvent = (QEvent::Type)QEvent::registerEventType();
QEvent::Type ClientEvents::SendPacketEvent = (QEvent::Type)QEvent::registerEventType();

SendPacketEvent::SendPacketEvent(const QByteArray p) : QEvent(ClientEvents::SendPacketEvent)
{
    pack = p;
}
