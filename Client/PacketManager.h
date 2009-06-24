#ifndef PACKETMANAGER_H
#define PACKETMANAGER_H

#include <QtGui>
#include <QObject>
#include <QDateTime>
#include    <QtGui/QApplication>
#include "../Common/Defines.h"
#include "../Common/CommInit.h"
#include "../Common/CommLogin.h"
#include "../Common/CommPlugin.h"
#include "../Common/CommPacket.h"
#include "../Common/CommData.h"
#include "../Common/CommError.h"
#include "ClientEvents.h"
#include "ClientApplication.h"
#include "ConfigManager.h"

class NetworkManager;

//! This Object is the manager for each packet readed on the socket
class   PacketManager : public QObject
{
    Q_OBJECT

    public:
        PacketManager(QObject* parent = 0);
        void        PacketToSend(QEvent *e);
    private slots:
        //! the callback for the sessionEnd timer
        void        sessionEnd();
    public slots:
         //! read the first CommPacket and go to the associed method
         /*!
              \param pac received packet to manage
          */
         void       packetReceived(QByteArray pac);

    private:
        //! enumerate the differents state of the client
        enum        tState {INIT, LOGIN_SESSION, LOGGED_IN, DISCONNECTED};
        //!  client's state
        tState      state;
        //! Queue contains packets to send
        QQueue<QByteArray> packetStack;
        //! Send all the packets contained in packetStack
        void        clearPacketStack();

        void        PacketError();
        void        PacketInit();
        void        PacketAlive();
        void        PacketLogin();
        void        PacketData();
        void        PacketPlugin();

        //! the received packet
        /*! every methods of PacketManager read and truncate this value
         */
        QByteArray  packet;

        //! corespondance table between CommPacket::type and the methods
        static void (PacketManager::*packetDirections[]) ();
    signals:
        //! signal emmitted to send a packet
        void sendPacket(const QByteArray&);
};

typedef void(PacketManager::*packetDirection)();

#endif // PACKETMANAGER_H
