#include "LoadPluginEvent.h"

QEvent::Type    LoadPluginEventType;

LoadPluginEvent::LoadPluginEvent() : QEvent::QEvent(LoadPluginEventType)
{
}
