#include <QtCore/QCoreApplication>

#include "Socket.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Socket s("localhost", 41412);

    return a.exec();
}
