#include "MainFrame.h"

#include <QDebug>

#include "../../ClientEvents.h"
#include "../../../Common/PluginManager.h"

#include "MainFrameWidget.h"

extern QEvent::Type ClientEvents::LoadPluginEvent;

MainFrame::MainFrame()
{
    widget = 0;
}

bool                MainFrame::event(QEvent *event)
{
    if (event->type() == ClientEvents::LoadPluginEvent)
        return (true);
    qDebug() << "MainFrame: Received Event not managed" << event;
    return (false);
}

QWidget             *MainFrame::getWidget()
{
    widget = new MainFrameWidget(this);
    widget->updateInfos();
//    connect(this, SIGNAL(infoUpdated(QHash<QString,QVariant>)), this->widget, SLOT(updateInfos(QHash<QString,QVariant>)));
//    if (this->userInfo.contains("Success") && this->userInfo.value("Success").toBool() == true)
//        this->infoUpdated(this->userInfo);
    return widget;
}

void MainFrame::courseClicked()
{
    emit switchToWidget(PluginManager().findPlugin<DisplayablePlugin*>("Course")->getWidget());
}
