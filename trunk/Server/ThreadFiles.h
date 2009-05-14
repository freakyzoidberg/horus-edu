#ifndef THREADFILES_H
#define THREADFILES_H

#include <QThread>

#include "FileServer.h"

class ThreadFiles : public QThread
{
  Q_OBJECT
public:
    ThreadFiles(QObject* parent=0);
    ~ThreadFiles();

protected:
    void run();

private:
    FileServer* server;
};

#endif // THREADFILES_H

