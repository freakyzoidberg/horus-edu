#include "ClientApplication.h"

#include <QLabel>

int main(int argc, char *argv[])
{
    ClientApplication a(argc, argv);
    return (a.exec());
}
