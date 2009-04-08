#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
    QCoreApplication::setOrganizationDomain(ORGANIZATION_DOMAIN);
    QCoreApplication::setApplicationName(CLIENT_NAME);
    QCoreApplication::setApplicationVersion(CLIENT_VERSION);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
