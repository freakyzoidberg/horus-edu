#include <QtPlugin>
#include <QObject>
#include "ClientApplication.h"

//Q_IMPORT_PLUGIN(testPlugin)

int main(int argc, char *argv[])
{

    ClientApplication a(argc, argv);
    return (a.exec());
}
