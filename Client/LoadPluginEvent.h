#ifndef LOADPLUGINEVENT_H
#define LOADPLUGINEVENT_H

#include <QEvent>
#include "../Common/Defines.h"

class LoadPluginEvent : public QEvent
{
public:
    LoadPluginEvent();

public:
    const static QEvent::Type    type = (QEvent::Type) LOADPLUGINEVENTTYPE;
};

#endif // LOADPLUGINEVENT_H
