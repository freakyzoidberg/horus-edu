//#define QT_NO_DEBUG_OUTPUT
#include <QtCore/QCoreApplication>
#include <QtNetwork>
#include <QtDebug>
#include <QThreadPool>
#include "Server.h"
#include "../Common/Defines.h"
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
    QCoreApplication::setOrganizationDomain(ORGANIZATION_DOMAIN);
    QCoreApplication::setApplicationName(SERVER_NAME);

    Server theserver;
    qDebug() << "main() Server Loaded";

    //plein de threads pour les test
    QThreadPool::globalInstance()->setMaxThreadCount(MAX_POOL_THREADS);

    return a.exec();
}
