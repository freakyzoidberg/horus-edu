#ifndef STOPEVENT_H
#define STOPEVENT_H

#include <QEvent>
#include "../Common/Defines.h"

class StopEvent : public QEvent
{
public:
    StopEvent();

public:
    const static QEvent::Type    type = (QEvent::Type) STOPEVENTTYPE;
};

#endif // STOPEVENT_H
