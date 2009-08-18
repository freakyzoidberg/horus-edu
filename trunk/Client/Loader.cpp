#include "Loader.h"

#include <QCoreApplication>

#include "ClientEvents.h"
#include "MetaManager.h"

Loader::Loader() : QDialog()
{
    this->ui.setupUi(this);
    this->ui.LoadingBar->setValue(0);
    this->processes = 0;
	foreach (AbstractManager *manager, MetaManager::getInstance()->findManagers())
	{
		++(this->processes);
		connect(manager, SIGNAL(loaded(int)), this, SLOT(load(int)));
		if (manager != MetaManager::getInstance()->findManager("NetworkManager"))
			QCoreApplication::postEvent(manager, new QEvent(ClientEvents::StartEvent));
	}
}

bool    Loader::event(QEvent *event)
{
	if (event->type() == QEvent::Close)
	{
        emit reject();
		return (true);
	}
    return (QDialog::event(event));
}

void	Loader::load(int percentage)
{
	int totalPercentage;

	foreach (AbstractManager *manager, MetaManager::getInstance()->findManagers())
	{
		if (manager == this->sender())
			percentage = percentage;
	}
	if (percentage > 100)
		percentage = 100;
	if (percentage < 0)
		percentage = 0;
	this->percentages.insert(this->sender(), percentage);
	totalPercentage = 0;
	foreach (int percentage, this->percentages)
		totalPercentage += percentage;
	this->ui.LoadingBar->setValue(totalPercentage / this->processes);
	if (totalPercentage / this->processes == 100)
		emit accept();
	if (this->sender() == MetaManager::getInstance()->findManager("PluginManager") && percentage == 100)
		QCoreApplication::postEvent(MetaManager::getInstance()->findManager("NetworkManager"), new QEvent(ClientEvents::StartEvent));

}
