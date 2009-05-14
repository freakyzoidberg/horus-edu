#include "ThreadFiles.h"

ThreadFiles::ThreadFiles(QObject* p) : QThread(p)
{
    server = new FileServer(this);
    start();
    qDebug() << "1";
}

ThreadFiles::~ThreadFiles()
{
    qDebug() << "2";
    delete server;
    qDebug() << "3";
}

void ThreadFiles::run()
{
    sleep(2);
    qDebug() << "yep";
}
