#ifndef CLIENTEVENTS_H
#define CLIENTEVENTS_H

#include <QEvent>
#include <QString>


class ClientEvents
{
    public:
        static QEvent::Type StartEvent;
        static QEvent::Type StopEvent;
        static QEvent::Type NetworkReceiveEvent;
        static QEvent::Type UnloadPluginEvent;
        static QEvent::Type InitEvent;
        static QEvent::Type LoadPluginEvent;
        static QEvent::Type LoginEvent;
};

class LoginEvent : public QEvent
{
        public:
            LoginEvent(QString l, QString p, uint t);

            QString login;
            QString pass;
            uint    typeL;
};

#endif // CLIENTEVENTS_H
