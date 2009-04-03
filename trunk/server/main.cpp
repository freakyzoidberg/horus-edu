//#define QT_NO_DEBUG_OUTPUT
#include <QtCore/QCoreApplication>
#include <QtNetwork>
#include <QtDebug>
#include <stdlib.h>
#include "fortuneserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    FortuneServer server;
    qDebug() << "Fortune Server Loaded";
    //connect();+
    return a.exec();
}
