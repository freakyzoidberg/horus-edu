#include "ThreadFiles.h"

ThreadFiles::ThreadFiles(QObject* p) : QThread(p)
{
    server = new FileServer(this);
    start();
}

ThreadFiles::~ThreadFiles()
{
    delete server;
}

void ThreadFiles::run()
{
    sleep(2);
    qDebug() << "yep";
    exec();
}
