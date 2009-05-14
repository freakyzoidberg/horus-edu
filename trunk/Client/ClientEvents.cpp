#include "ClientEvents.h"

QEvent::Type ClientEvents::StartEvent = (QEvent::Type)QEvent::registerEventType();
QEvent::Type ClientEvents::StopEvent = (QEvent::Type)QEvent::registerEventType();
QEvent::Type ClientEvents::NetworkReceiveEvent = (QEvent::Type)QEvent::registerEventType();
QEvent::Type ClientEvents::UnloadPluginEvent = (QEvent::Type)QEvent::registerEventType();
QEvent::Type ClientEvents::InitEvent = (QEvent::Type)QEvent::registerEventType();
QEvent::Type ClientEvents::LoadPluginEvent = (QEvent::Type)QEvent::registerEventType();
QEvent::Type ClientEvents::LoginEvent = (QEvent::Type)QEvent::registerEventType();

LoginEvent::LoginEvent(QString l, QString p, uint t) : QEvent(ClientEvents::LoginEvent)
{
    login = l;
    pass = p;
    this->typeL = t;
}
