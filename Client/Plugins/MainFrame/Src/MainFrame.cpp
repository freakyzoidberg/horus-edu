#include "MainFrame.h"

#include <QDebug>

#include "../../ClientEvents.h"
#include "../../../Common/PluginManager.h"
#include "../../../Common/TreeDataPlugin.h"

#include "MainFrameWidget.h"

QEvent::Type ClientEvents::LoadPluginEvent;

MainFrame::MainFrame()
{
    widget = 0;
}

bool MainFrame::canLoad() const
{
	if (pluginManager->findPlugin<TreeDataPlugin*>())
		return (true);
	return (false);
}

void MainFrame::load()
{
    TreeDataPlugin* t = pluginManager->findPlugin<TreeDataPlugin*>();
    if ( ! t->isLoaded())
        t->load();

    widget = new MainFrameWidget(this);
    Plugin::load();
}

void MainFrame::unload()
{
    delete widget;
    Plugin::unload();
}

QWidget* MainFrame::getWidget()
{
// normaly cannot happend
//    if ( ! widget)
//        return 0; // -> not loaded

    widget->updateInfos();
//    connect(this, SIGNAL(infoUpdated(QHash<QString,QVariant>)), this->widget, SLOT(updateInfos(QHash<QString,QVariant>)));
//    if (this->userInfo.contains("Success") && this->userInfo.value("Success").toBool() == true)
//        this->infoUpdated(this->userInfo);
    return widget;
}

void MainFrame::courseClicked()
{
    emit switchToWidget(pluginManager->findPlugin<DisplayablePlugin*>("Course")->getWidget());
}
