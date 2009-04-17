#ifndef CLIENTEVENTS_H
#define CLIENTEVENTS_H

#include <QEvent>

namespace ClientEvents
{
    const static QEvent::Type MyEvent1 = (QEvent::Type)QEvent::registerEventType();
    const static QEvent::Type MyEvent2 = (QEvent::Type)QEvent::registerEventType();
    const static QEvent::Type MyEvent3 = (QEvent::Type)QEvent::registerEventType();
    const static QEvent::Type MyEventWithContent = (QEvent::Type)QEvent::registerEventType();
}

class MyEventWithContent : public QEvent
{
public:
    inline MyEventWithContent(char* content) : QEvent(ClientEvents::MyEventWithContent) { aFooContent = content; };

    char* aFooContent;
};

#endif // CLIENTEVENTS_H
