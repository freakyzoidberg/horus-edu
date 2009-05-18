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
    static QThread* instance();

protected:
    void run();

private:
    static ThreadFiles* _instance;
};

#endif // THREADFILES_H

