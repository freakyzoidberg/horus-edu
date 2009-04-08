#ifndef CLIENTAPPLICATION_H
#define CLIENTAPPLICATION_H

#include <QtGui/QApplication>
#include "IClientPlugin.h"

class ClientApplication : public QApplication
{
public:
    ClientApplication(int argc, char *argv[]);
    ~ClientApplication();
    bool    init();
    bool    reloadPlugins();
    bool    restartNetwork();

private:
    bool    loadPlugins();
    bool    unloadPlugins();
    bool    startNetwork();
    bool    stopNetwork();
};

#endif // CLIENTAPPLICATION_H
