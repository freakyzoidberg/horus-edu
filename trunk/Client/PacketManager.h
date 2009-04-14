#ifndef PACKETMANAGER_H
#define PACKETMANAGER_H

#include <QtGui>
#include <QObject>

#include "../Common/Defines.h"
#include "../Common/CommInit.h"
#include "../Common/CommLogin.h"
#include "../Common/CommModule.h"
#include "../Common/CommPacket.h"
#include "../Common/CommError.h"

class   PacketManager : public QObject
{
  Q_OBJECT

public:
    PacketManager(QObject* parent = 0);

public slots:
     void       packetReceived(QByteArray pac);

private:
    enum        tState {DISCONNECTED, LOGGED_OUT, LOGGED_IN};
    tState      state;

    void        PacketError();
    void        PacketInit();
    void        PacketAlive();
    void        PacketLogin();
    void        PacketFile();
    void        PacketConfig();
    void        PacketModule();

    QByteArray  packet;
    static void (PacketManager::*packetDirections[]) ();

signals:
    void sendPacket(QByteArray packet);
};

typedef void(PacketManager::*packetDirection)();

#endif // PACKETMANAGER_H
