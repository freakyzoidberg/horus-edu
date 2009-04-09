#include "StopEvent.h"

QEvent::Type    StopEventType;

StopEvent::StopEvent() : QEvent::QEvent(StopEventType)
{
}
