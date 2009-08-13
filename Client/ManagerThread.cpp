#include "ManagerThread.h"

#include <QCoreApplication>

#include "ManagerFactory.h"
#include "ClientEvents.h"

ManagerThread::ManagerThread(QString managerName) : QThread()
{
	this->embedded = 0;
	this->_managerName = managerName;
	this->start();
}

ManagerThread::~ManagerThread()
{
	this->quit();
}

void ManagerThread::run()
{
	ManagerFactory factory;

	this->init.lock();
	this->embedded = factory.getManager(this->_managerName);
	QThread::QObject::connect(this->embedded, SIGNAL(notified), (QObject *)(QThread *)this, SLOT(notify));
	QThread::QObject::connect(this->embedded, SIGNAL(loaded), (QObject *)(QThread *)this, SLOT(load));
	this->init.unlock();
	if (this->embedded)
		this->exec();
}

bool ManagerThread::event(QEvent *event)
{
	if (event->type() >= QEvent::User)
	{
		this->init.lock();
		if (!(this->embedded))
		{
			this->init.unlock();
			return (false);
		}
		this->init.unlock();
        if (event->type() == ClientEvents::SendPacketEvent)
        {
            SendPacketEvent *newEvent = new SendPacketEvent(*(static_cast<SendPacketEvent *>(event)));
            QCoreApplication::postEvent(this->embedded, newEvent);
        }
        else if (event->type() == ClientEvents::SendLoginEvent)
        {
            SendLoginEvent *newEvent = new SendLoginEvent(*(static_cast<SendLoginEvent *>(event)));
			QCoreApplication::postEvent(this->embedded, newEvent);
        }
        else
			QCoreApplication::postEvent(this->embedded, new QEvent(event->type()));
		return (true);
	}
	return (QThread::event(event));
}

void ManagerThread::notify(QString message)
{
	emit notified(message);
}

void ManagerThread::load(int percentage)
{
	emit loaded(percentage);
}
