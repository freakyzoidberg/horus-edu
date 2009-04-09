#ifndef STARTEVENT_H
#define STARTEVENT_H

#include <QEvent>
#include "../Common/Defines.h"

class StartEvent : public QEvent
{
public:
    StartEvent();

public:
    const static QEvent::Type    type = (QEvent::Type) STARTEVENTTYPE;
};

#endif // STARTEVENT_H
