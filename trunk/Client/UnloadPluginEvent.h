#ifndef UNLOADPLUGINEVENT_H
#define UNLOADPLUGINEVENT_H

#include <QEvent>
#include "../Common/Defines.h"

class UnloadPluginEvent : public QEvent
{
public:
    UnloadPluginEvent();

public:
    const static QEvent::Type    type = (QEvent::Type) UNLOADPLUGINEVENTTYPE;
};

#endif // UNLOADPLUGINEVENT_H
