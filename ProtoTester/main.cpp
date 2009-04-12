#include <QtCore/QCoreApplication>

#include "Socket.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Socket s(argv[1], 42000);

    return a.exec();
}
