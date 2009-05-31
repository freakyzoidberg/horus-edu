#ifndef THREADNETWORK_H
#define THREADNETWORK_H

#include <QThread>
#include "NetworkManager.h"
#include "ClientApplication.h"

class ThreadNetwork : public QThread
{
    Q_OBJECT
    public:
        ~ThreadNetwork();
        NetworkManager *nM;
        static  ThreadNetwork* getInstance(ClientApplication *parent = 0);
    protected:
        void run();
    private:

        ThreadNetwork(ClientApplication* parent=0);
        //! flag for the singleton
        static bool instanceFlag;
        //! the instance of the singleton
        static ThreadNetwork *single;
        ClientApplication *parent;
    protected slots:
        //! event loop
        bool    event(QEvent *e);
};

#endif // THREADNETWORK_H
