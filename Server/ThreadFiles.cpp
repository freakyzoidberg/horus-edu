#include "ThreadFiles.h"

ThreadFiles* ThreadFiles::_instance = 0;

ThreadFiles::ThreadFiles(QObject* p) : QThread(p)
{
    _instance = this;
    start();
}

ThreadFiles::~ThreadFiles()
{
}

void ThreadFiles::run()
{
    FileServer server;
    exec();
}

QThread* ThreadFiles::instance()
{
    return _instance;
}
