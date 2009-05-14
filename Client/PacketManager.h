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
#include "../Common/CommError.h"
#include "ClientEvents.h"


//! This Object is the manager for each packet readed on the socket
class   PacketManager : public QObject
{
  Q_OBJECT

public:
    PacketManager(QObject* parent = 0);

public slots:
     //! read the first CommPacket and go to the associed method
     /*!
          \param pac received packet to manage
      */
     void       packetReceived(QByteArray pac);

private:
    //! enumerate the differents state of the client
    enum        tState {INIT, LOGGED_OUT, LOGGED_IN, DISCONNECTED};
    //!  client's state
    tState      state;
    //!  PacketManager's parent to send event to NetworkManager
    QObject *parent;

    void        PacketError();
    void        PacketInit();
    void        PacketAlive();
    void        PacketLogin();
    void        PacketFile();
    void        PacketConfig();
    void        PacketPlugin();

    //! the received packet
    /*! every methods of PacketManager read and truncate this value
     */
    QByteArray  packet;

    //! corespondance table between CommPacket::type and the methods
    static void (PacketManager::*packetDirections[]) ();
};

typedef void(PacketManager::*packetDirection)();

#endif // PACKETMANAGER_H
