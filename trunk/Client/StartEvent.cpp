#include            "StartEvent.h"

QEvent::Type    StartEventType;


StartEvent::StartEvent() : QEvent::QEvent(StartEventType)
{
}
