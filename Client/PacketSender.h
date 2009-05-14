#ifndef PACKETSENDER_H
#define PACKETSENDER_H

#include <QObject>
#include <QtGui>
#include <QDateTime>

#include "../Common/Defines.h"
#include "../Common/CommInit.h"
#include "../Common/CommLogin.h"
#include "../Common/CommPlugin.h"
#include "../Common/CommPacket.h"
#include "../Common/CommError.h"
#include "ClientEvents.h"


//! This Object is the manager for each packet the client want to send
class PacketSender : public QObject
{

    Q_OBJECT
    public:
        PacketSender(QObject* parent = 0);

    public slots:
        //! read the type of packet and go to the associed method
       /*!
          \param t type of the packet
          \param e event wich contains data to link with the packet
        */
        void        PacketToSend(uint t, QEvent *e);

    private:
        //! enumerate the differents state of the client
        enum        tState {INIT, LOGGED_OUT, LOGGED_IN, DISCONNECTED};
        //!  client's state
        tState      state;
        //!  PacketSender's parent to send event to NetworkManager
        QObject *parent;

        void        PacketError();
        void        PacketInit();
        void        PacketAlive();
        void        PacketLogin();
        void        PacketFile();
        void        PacketConfig();
        void        PacketModule();
        //!   event contain the data to send
        QEvent      *ev;
        //! corespondance table between CommPacket::type and the methods
        static void (PacketSender::*packetDirectionsToSend[]) ();

    signals:
        //! signal emmited when a packet need to be send to the client
        void sendPacket(QByteArray packet);
};

typedef void(PacketSender::*packetDirectionToSend)();

#endif // PACKETSENDER_H
