//#define QT_NO_DEBUG_OUTPUT
#include <QtCore/QCoreApplication>
#include <QtNetwork>
#include <QtDebug>
#include "Server.h"
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setOrganizationName("HorusEIP");
    QCoreApplication::setOrganizationDomain("hor.us");
    QCoreApplication::setApplicationName("Horus Server");
    Server theserver;
    qDebug() << "main() Server Loaded";

    return a.exec();
}
