#include "ClientApplication.h"
#include "../Common/Defines.h"

ClientApplication::ClientApplication(int argc, char *argv[]) : QApplication(argc, argv)
{
}

ClientApplication::~ClientApplication()
{
    this->unloadPlugins();
    this->stopNetwork();
}

bool    ClientApplication::init()
{
    QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
    QCoreApplication::setOrganizationDomain(ORGANIZATION_DOMAIN);
    QCoreApplication::setApplicationName(CLIENT_NAME);
    QCoreApplication::setApplicationVersion(CLIENT_VERSION);
    this->loadPlugins();
    this->startNetwork();
    return (true);
}

bool    ClientApplication::loadPlugins()
{
    return (true);
}

bool    ClientApplication::unloadPlugins()
{
    return (true);
}

bool    ClientApplication::reloadPlugins()
{
    this->unloadPlugins();
    return (this->loadPlugins());
}

bool    ClientApplication::startNetwork()
{
    return (true);
}

bool    ClientApplication::stopNetwork()
{
    return (true);
}

bool    ClientApplication::restartNetwork()
{
    this->stopNetwork();
    return (this->startNetwork());
}

