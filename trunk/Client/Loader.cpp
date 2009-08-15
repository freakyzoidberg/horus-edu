#include "Loader.h"

#include <QCoreApplication>

//#include "../Common/SettingsDataPlugin.h"
//#include "../Common/SettingsData.h"

#include "ClientEvents.h"
#include "MetaManager.h"
//#include "PluginManagerClient.h"

Loader::Loader() : QDialog()
{
    this->ui.setupUi(this);
    this->ui.LoadingBar->setValue(0);
    this->processes = 0;
    this->processesComplete = 0;
    this->loadNetwork();
    this->loadSettings();
    this->loadPlugins();
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

void    Loader::loadSettings()
{
//    ++(this->processes);
//    settings->getSettings("", SettingsData::CLIENT_USER_SCOPE, PluginManagerClient::instance()->currentUser())->update();
//    QApplication::postEvent(config, new QEvent(ClientEvents::StartEvent));
}

bool    Loader::event(QEvent *event)
{
    if (event->type() == ClientEvents::StartEvent)
    {
        ++(this->processesComplete);
        this->ui.LoadingBar->setValue(100 * this->processesComplete / this->processes);
        if (processes == processesComplete)
			emit accept();
        return (true);
    }
    else if (event->type() == ClientEvents::StopEvent)
    {
        --(this->processesComplete);
        this->ui.LoadingBar->setValue(100 * this->processesComplete / this->processes);
        if (0 == processesComplete)
	        emit reject();
        return (true);
    }
    else if (event->type() == QEvent::Close)
	{
        emit reject();
		return (true);
	}
    return (QDialog::event(event));
}
