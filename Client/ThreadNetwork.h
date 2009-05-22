#ifndef THREADNETWORK_H
#define THREADNETWORK_H

#include <QThread>
#include "NetworkManager.h"

class ThreadNetwork : public QThread
{
    Q_OBJECT
    public:
        ~ThreadNetwork();
        NetworkManager *nM;
        static  ThreadNetwork* getInstance(QObject *parent);
    protected:
        void run();
    private:

        ThreadNetwork(QObject* parent=0);
        //! flag for the singleton
        static bool instanceFlag;
        //! the instance of the singleton
        static ThreadNetwork *single;
        QObject *parent;
    protected slots:
        //! event loop
        bool    event(QEvent *e);
};

#endif // THREADNETWORK_H
