#include <QtCore/QCoreApplication>

#include "Socket.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Socket s("localhost", 42000);

    return a.exec();
}
