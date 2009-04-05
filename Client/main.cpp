#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Horus Inc.");
    QCoreApplication::setOrganizationDomain("4--2.net");
    QCoreApplication::setApplicationName("Horus Client");
    QCoreApplication::setApplicationVersion("0.01");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
