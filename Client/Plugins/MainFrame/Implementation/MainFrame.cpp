#include "MainFrame.h"

#include <QDebug>

#include "../../ClientEvents.h"

#include "MainFrameWidget.h"

Q_EXPORT_PLUGIN2(MainFrame, MainFrame)

extern QEvent::Type ClientEvents::LoadPluginEvent;

MainFrame::MainFrame()
{
    this->widget = 0;
}

const QByteArray    MainFrame::getName() const
{
    return ("MainFrame");
}

const QByteArray    MainFrame::getVersion() const
{
    return ("0.1");
}

QStringList         MainFrame::getPluginsRequired() const
{
    return (QStringList());
}

QStringList         MainFrame::getPluginsConflicts() const
{
    return (QStringList());
}

QStringList         MainFrame::getPluginsRecommended() const
{
    return (QStringList());
}

bool                MainFrame::event(QEvent *event)
{
    QVariantHash request;

    request["Request"] = "getUserInfo";
    network->sendPacket(PluginPacket("UserManagment", request));
    if (event->type() == ClientEvents::LoadPluginEvent)
        return (true);
    qDebug() << "MainFrame: Received Event not managed" << event;
    return (false);
}

QWidget             *MainFrame::getWidget()
{
    this->widget = new MainFrameWidget(this);
    connect(this, SIGNAL(infoUpdated(QHash<QString,QVariant>)), this->widget, SLOT(updateInfos(QHash<QString,QVariant>)));
    if (this->userInfo.contains("Success") && this->userInfo.value("Success").toBool() == true)
        this->infoUpdated(this->userInfo);
    return (this->widget);
}

void                MainFrame::recvPacket(const PluginPacket &packet)
{
    if (packet.data.toHash().value("Success").toBool() == true)
        this->userInfo = packet.data.toHash();
    this->infoUpdated(this->userInfo);
}
