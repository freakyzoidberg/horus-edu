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
    if (!server.isListening())
        qDebug() << "Server Dont Listen";
    else
    {
        qDebug() << "Server Listen on port";
        qDebug("port : %d", server.serverPort());
    }
    //connect();+
    return a.exec();
}
