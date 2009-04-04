#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QCoreApplication::setOrganizationName("Horus Inc.");
    QCoreApplication::setOrganizationDomain("4--2.net");
    QCoreApplication::setApplicationName("Horus Client");
    QCoreApplication::setApplicationVersion("0.01");
    w.show();
    return a.exec();
}
