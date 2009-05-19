#include <QtCore/QCoreApplication>

#include "Socket.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    char* host = "localhost";
    if (argc > 1)
        host = argv[1];

    Socket s(host, 42000);

    return a.exec();
}
