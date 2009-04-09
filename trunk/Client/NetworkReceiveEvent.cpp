#include "NetworkReceiveEvent.h"

QEvent::Type    NetworkReceiveEventType;

NetworkReceiveEvent::NetworkReceiveEvent() : QEvent::QEvent(NetworkReceiveEventType)
{
}
