#include "UnloadPluginEvent.h"

QEvent::Type    UnloadPluginEventType;

UnloadPluginEvent::UnloadPluginEvent() : QEvent::QEvent(UnloadPluginEventType)
{
}
