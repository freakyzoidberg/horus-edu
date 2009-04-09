#include "UnloadPluginEvent.h"

UnloadPluginEvent::UnloadPluginEvent() : QEvent::QEvent(UnloadPluginEvent::type)
{
}
