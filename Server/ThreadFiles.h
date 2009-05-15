#ifndef THREADFILES_H
#define THREADFILES_H

#include <QThread>

#include "FileServer.h"

//! class creating the thread for the FileServer
class ThreadFiles : public QThread
{
  Q_OBJECT
public:
    ThreadFiles(QObject* parent=0);
    ~ThreadFiles();

protected:
    void run();

private:
    //! contain the server for files transfert
    FileServer* server;
};

#endif // THREADFILES_H

