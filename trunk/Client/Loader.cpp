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
		QCoreApplication::postEvent(manager, new QEvent(ClientEvents::StartEvent));
		connect(manager, SIGNAL(loaded(int)), this, SLOT(load(int)));
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
	{
		QCoreApplication::postEvent(MetaManager::getInstance()->findManager("PluginManager"), ClientEvents::LoadPluginEvent);
		emit accept();
	}
}
