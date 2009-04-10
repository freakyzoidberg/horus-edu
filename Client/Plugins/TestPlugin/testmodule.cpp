#include <QtCore/qplugin.h>
#include <QDebug>
#include <iostream>
#include "testmodule.h"

#include "../../NetworkReceiveEvent.h"
#include "../../UnloadPluginEvent.h"

Q_EXPORT_PLUGIN2("testPlugin", TestModule)

TestModule::TestModule()
{
    std::cout << "module testPlugin loaded." << std::endl;
}

bool    TestModule::event(QEvent *event)
{
    bool    eventSuccess;

    if (event->type() == NetworkReceiveEvent::type)
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
    else if (event->type() == UnloadPluginEvent::type)
    {
        event->accept();
        return eventHandlerUnload(event);
    }
    event->ignore();
    return QObject::event(event);
}

bool    TestModule::eventHandlerLoad(QEvent *event)
{
    qDebug()  << "Handling event loadModule"
            << "isAccepted:"    << event->isAccepted()
            << "spontaneous:"   << event->spontaneous();
    return true;
}

bool    TestModule::eventHandlerUnload(QEvent *event)
{
    qDebug()  << "Handling event UnlodModule"
            << "isAccepted:" << event->isAccepted()
            << "spontaneous:" << event->spontaneous();
    return true;
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

