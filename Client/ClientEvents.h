#ifndef CLIENTEVENTS_H
#define CLIENTEVENTS_H

#include <QEvent>
#include <QString>
#include "../Common/CommPacket.h"

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
        //! event to load a plugin
        static QEvent::Type LoadPluginEvent;
        //!  event to send a packet to the serv
        static QEvent::Type SendPacketEvent;
        //!  event to recv a packet from the serv
        static QEvent::Type RecvPacketEvent;
        //!  event to show the login window
        static QEvent::Type ShowLoginEvent;
        //!  event to hide the login window
        static QEvent::Type HideLoginEvent;
        //!  event to send the login to server
        static QEvent::Type SendLoginEvent;
};

//! this object is an event containt a packet to send to the server
class SendPacketEvent : public QEvent
{
        public:
            SendPacketEvent(const QByteArray p);
            SendPacketEvent(const SendPacketEvent &s);
            //! packet to send
            QByteArray pack;
};

//! this object is an event containt a packet received from the server
class RecvPacketEvent : public QEvent
{
        public:
            RecvPacketEvent(const QByteArray p);

            //! packet to send
            QByteArray pack;
};

//! this object is an event containt a packet to send to the server
class SendLoginEvent : public QEvent
{
        public:
            SendLoginEvent(const QByteArray p);
            SendLoginEvent(const SendLoginEvent &s);

            //! packet to send
            QByteArray pack;
};
#endif // CLIENTEVENTS_H
