#include "ThreadNetwork.h"

ThreadNetwork::ThreadNetwork(QObject* p) : QThread(p)
{
    this->parent = p;
    start();
}

void ThreadNetwork::run()
{
     nM = new NetworkManager(this->parent);
     exec();
}

bool ThreadNetwork::event(QEvent *e)
{
    if (e->type() >= QEvent::User)
    {
        if (e->type() == ClientEvents::SendPacketEvent)
        {
            SendPacketEvent *spe = new SendPacketEvent(*(static_cast<SendPacketEvent *>(e)));
            QApplication::postEvent(nM, spe);
        }
        else if (e->type() == ClientEvents::SendLoginEvent)
        {
            SendLoginEvent *l = new SendLoginEvent(*(static_cast<SendLoginEvent *>(e)));
            QApplication::postEvent(nM, l);
        }
        else
            QApplication::postEvent(nM, new QEvent(e->type()));
        return true;
    }
    else
        return QThread::event(e);
}

bool ThreadNetwork::instanceFlag = false;
ThreadNetwork* ThreadNetwork::single = NULL;
ThreadNetwork* ThreadNetwork::getInstance(QObject *parent)
{
    if(! instanceFlag)
    {
        single = new ThreadNetwork(parent);
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}
ThreadNetwork::~ThreadNetwork()
{
    instanceFlag = false;
}
