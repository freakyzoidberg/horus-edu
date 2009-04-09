#ifndef NETWORKRECEIVEEVENT_H
#define NETWORKRECEIVEEVENT_H

#include <QEvent>
#include "../Common/Defines.h"

class NetworkReceiveEvent : public QEvent
{
public:
    NetworkReceiveEvent();

public:
    const static QEvent::Type    type = (QEvent::Type) NETWORKRECEIVEEVENTTYPE;
};

#endif // NETWORKRECEIVEEVENT_H
