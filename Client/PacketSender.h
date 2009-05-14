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


class PacketSender : public QObject
{

    Q_OBJECT
    public:
        PacketSender(QObject* parent = 0);

    public slots:
        void        PacketToSend(uint t, QEvent *e);

    private:
        enum        tState {INIT, LOGGED_OUT, LOGGED_IN, DISCONNECTED};
        tState      state;
        QObject *parent;

        void        PacketError();
        void        PacketInit();
        void        PacketAlive();
        void        PacketLogin();
        void        PacketFile();
        void        PacketConfig();
        void        PacketModule();

        QEvent      *ev;
        QByteArray  packet;
        static void (PacketSender::*packetDirectionsToSend[]) ();

    signals:
        void sendPacket(QByteArray packet);
};

typedef void(PacketSender::*packetDirectionToSend)();

#endif // PACKETSENDER_H
