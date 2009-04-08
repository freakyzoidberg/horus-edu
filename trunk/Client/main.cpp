#include "ClientApplication.h"

int main(int argc, char *argv[])
{
    ClientApplication a(argc, argv);
    if (a.init())
        return (a.exec());
    else
        return (-1);
}
