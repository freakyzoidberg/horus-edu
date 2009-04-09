#include <QtCore/qplugin.h>
#include <iostream>
#include "testmodule.h"

Q_EXPORT_PLUGIN2("testPlugin", TestModule)

TestModule::TestModule()
{
    std::cout << "module testPlugin loaded." << std::endl;
}

bool    TestModule::event(QEvent *event)
{
    bool    eventSuccess;

    if (event->type() == QEvent::None)
    {
        event->accept();
        pNetwork = new PluginNetwork(event);
        eventSuccess = pNetwork->eventHandler();
        delete pNetwork;
        return eventSuccess;
    }
    else if (event->type() == LoadPluginEvent::type)
    {
        event->accept();
        return eventHandlerLoad(event);
    }
    else if (event->type() == QEvent::None)
    {
        event->accept();
        return eventHandlerUnload();
    }
    event->ignore();
    return QObject::event(event);
}

bool    TestModule::eventHandlerLoad(QEvent *event)
{
    std::cout << "Handling event loadModule" << std::endl;
    std::cout << "isAccepted:" << event->isAccepted() << std::endl;
    std::cout << "spontaneous:" << event->spontaneous() << std::endl;
    return true;
}

bool    TestModule::eventHandlerUnload()
{
    return false;
}

void TestModule::setModName(const QString modName)
{
    this->modName = modName;
}

void    TestModule::setModVersion(const QString modVersion)
{
    this->modVersion = modVersion;
}

void    TestModule::setModRequired(const QString name)
{
    modRequired << name;
}

void    TestModule::setModConflicts(const QString name)
{
    modConflicts << name;
}

void    TestModule::setExports(const QString name)
{
    exports << name;
}

void    TestModule::setModRecommended(const QString name)
{
    modRecommended << name;
}

QString   TestModule::getName() const
{
    return modName;
}

QString   TestModule::getVersion() const
{
    return modVersion;
}

QStringList   TestModule::getPluginsConflicts() const
{
    return modConflicts;
}

QStringList   TestModule::getPluginsRequired() const
{
    return modRequired;
}

QStringList   TestModule::getPluginsRecommended() const
{
    return modRecommended;
}

QStringList   TestModule::getExports() const
{
    return exports;
}

