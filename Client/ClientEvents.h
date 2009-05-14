#ifndef CLIENTEVENTS_H
#define CLIENTEVENTS_H

#include <QEvent>
#include <QString>

//! this Object contains all the client events types
class ClientEvents
{
    public:
        //! event to start the application
        static QEvent::Type StartEvent;
        //! event to end the application
        static QEvent::Type StopEvent;
        //! event for the networkManager
        static QEvent::Type NetworkReceiveEvent;
        //! event to unload a plugin
        static QEvent::Type UnloadPluginEvent;
        //! event for the init packet in PacketManager
        static QEvent::Type InitEvent;
        //! event to load a plugin
        static QEvent::Type LoadPluginEvent;
        //!  event to login in the serv
        static QEvent::Type LoginEvent;
};

//! this object is an event with data to login in the server
class LoginEvent : public QEvent
{
        public:
            LoginEvent(QString l, QString p, uint t);

            //! username
            QString login;
            //! password
            QString pass;
            //! type of login
            uint    typeL;
};

#endif // CLIENTEVENTS_H
