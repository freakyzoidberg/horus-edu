#include "ThreadNetwork.h"

ThreadNetwork::ThreadNetwork(ClientApplication* p) : QThread(p)
{
    this->parent = p;
    nM = 0;
    start();
}

void ThreadNetwork::run()
{
     mutex.lock();
     nM = new NetworkManager(this->parent);
     mutex.unlock();
     exec();
}

bool ThreadNetwork::event(QEvent *e)
{
    mutex.lock();
    if (e->type() >= QEvent::User)
    {
        if (e->type() == ClientEvents::StopEvent)
        {
            QApplication::postEvent(this->parent->loader, new QEvent(ClientEvents::StopEvent));
            this->exit(0);// a modif pour que ca coupe bien le reseau, je te laisse faire ca abder ;)
        }
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
        mutex.unlock();
        return true;
    }
    else
        return QThread::event(e);
}

bool ThreadNetwork::instanceFlag = false;
ThreadNetwork* ThreadNetwork::single = NULL;
ThreadNetwork* ThreadNetwork::getInstance(ClientApplication *parent)
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
