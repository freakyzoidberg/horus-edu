#include "PacketSender.h"

PacketSender::PacketSender(QObject* parent) : QObject(parent)
{
    this->parent = parent;
    state = DISCONNECTED;
}

packetDirectionToSend PacketSender::packetDirectionsToSend[] =
{
    0,//for CommPacket::UNKNOW
    &PacketSender::PacketError,
    &PacketSender::PacketInit,
    &PacketSender::PacketAlive,
    &PacketSender::PacketLogin,
    &PacketSender::PacketFile,
    &PacketSender::PacketConfig,
    &PacketSender::PacketModule
};

void PacketSender::PacketToSend(uint t, QEvent *e)
{
    ev = e;
    (this->*packetDirectionsToSend[ t ])();
}

void PacketSender::PacketError()
{

}

void PacketSender::PacketInit()
{
    CommInit i(0, CLIENT_NAME);

    //TODO add protocol version compatible check
    emit sendPacket(i.getPacket());

    QSettings settings;
    settings.beginGroup("SESSIONS");
    if (settings.value("sessionEnd", 0).toUInt() > (QDateTime::currentDateTime().toTime_t() + 60))
    {
        LoginEvent *e = new LoginEvent(settings.value("sessionLogin", "").toString(),settings.value("sessionString", "").toString(), 2);
        QApplication::postEvent(this->parent, e);
    }
    else
    {
                //this->hide();
                //parent->ld->show();
                //return true;
    }
    settings.endGroup();
    qDebug() << "[out]" << i;
    state = LOGGED_OUT;
}

void PacketSender::PacketAlive()
{
    qDebug() << "[ out] Alive";
}

void PacketSender::PacketLogin()
{
    if (state != LOGGED_OUT)
        return;
    QSettings   settings;
    LoginEvent *le = static_cast<LoginEvent *>(ev);

    settings.beginGroup("SESSIONS");
    if (le->typeL == 1)
    {
        settings.setValue("sessionString", "");
        settings.setValue("sessionLogin", le->login);
        settings.setValue("sessionTime", "");
        settings.setValue("sessionEnd", "");
        CommLogin  l(CommLogin::LOGIN_PASSWORD);
        l.login = le->login;
        l.sha1Pass = QCryptographicHash::hash(le->pass.toUtf8(), QCryptographicHash::Sha1);
        emit sendPacket(l.getPacket());
        qDebug() << "[out]" << l;
    }
    else if (le->typeL == 2)
    {
        CommLogin  ls(CommLogin::LOGIN_SESSION);
        ls.login = settings.value("sessionLogin", "").toString();
        ls.sessionString = settings.value("sessionString", "").toByteArray();
        emit sendPacket(ls.getPacket());
        qDebug() << "[out]" << ls;
    }
    else if (le->typeL == 3)
    {
    }
    settings.endGroup();
}

void PacketSender::PacketFile()
{
}

void PacketSender::PacketConfig()
{
}

void PacketSender::PacketModule()
{
}
