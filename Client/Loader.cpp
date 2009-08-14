#include "Loader.h"

#include <QCoreApplication>

#include "../Common/SettingsDataPlugin.h"
#include "../Common/SettingsData.h"

#include "ClientEvents.h"
#include "LoginDialog.h"
#include "MainWindow.h"
#include "PluginManagerClient.h"
#include "MetaManager.h"

Loader::Loader(ClientApplication *parent) : QDialog()
{
    this->parent = parent;
    this->ui.setupUi(this);
    this->ui.LoadingBar->setValue(0);
    this->processes = 0;
    this->processesComplete = 0;
    this->loadNetwork();
    //this->loadSettings();
    this->loadPlugins();
    ld = new LoginDialog();
}

void    Loader::loadNetwork()
{
    ++(this->processes);
	QCoreApplication::postEvent(MetaManager::getInstance()->findManager("NetworkManager"), new QEvent(ClientEvents::StartEvent));
}

void    Loader::loadPlugins()
{
    ++(this->processes);
	QCoreApplication::postEvent(MetaManager::getInstance()->findManager("PluginManager"), new QEvent(ClientEvents::StartEvent));
}

//void    Loader::loadSettings()
//{
//    ++(this->processes);
//    settings->getSettings("", SettingsData::CLIENT_USER_SCOPE, PluginManagerClient::instance()->currentUser())->update();
//    QApplication::postEvent(config, new QEvent(ClientEvents::StartEvent));
//}

bool    Loader::event(QEvent *event)
{
    if (event->type() == ClientEvents::StartEvent)
    {
        event->accept();
        ++(this->processesComplete);
        this->ui.LoadingBar->setValue(100 * this->processesComplete / this->processes);
        if (processes == processesComplete)
        {
            this->hide();
            parent->mainWindow = new MainWindow(this->parent);
            parent->mainWindow->show();
        }
        return (true);
    }
    else if (event->type() == ClientEvents::StopEvent)
    {
        event->accept();
        --(this->processesComplete);
        this->ui.LoadingBar->setValue(100 * this->processesComplete / this->processes);
        if (0 == processesComplete)
            ClientApplication::exit(0);
        return (true);
    }
    else if (event->type() == ClientEvents::ShowLoginEvent)
    {
        ld->show();
    }
    else if (event->type() == ClientEvents::HideLoginEvent)
    {

        if (ld != NULL)
        {
            ld->hide();
            delete ld;
        }
    }
    if (event->type() == QEvent::Close)
        this->parent->preExit();
    return (QDialog::event(event));
}
