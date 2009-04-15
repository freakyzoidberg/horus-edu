#include <QtCore/qplugin.h>
#include <QDebug>
#include <iostream>
#include "testmodule.h"

#include "../../NetworkReceiveEvent.h"
#include "../../UnloadPluginEvent.h"

Q_EXPORT_PLUGIN2(testModule, testPlugin)

testPlugin::testPlugin()
{
    std::cout << "module testPlugin loaded." << std::endl;
    pNetwork = new PluginNetwork();
}

testPlugin::~testPlugin()
{
    delete pNetwork;
}

bool    testPlugin::event(QEvent *event)
{
    bool    eventSuccess;

    if (event->type() == NetworkReceiveEvent::type)
    {
        event->accept();        
        return pNetwork->eventHandler(event);
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

bool    testPlugin::eventHandlerLoad(QEvent *event)
{
    qDebug()  << "Handling event loadModule"
            << "isAccepted:"    << event->isAccepted()
            << "spontaneous:"   << event->spontaneous();
    return true;
}

bool    testPlugin::eventHandlerUnload(QEvent *event)
{
    qDebug()  << "Handling event UnlodModule"
            << "isAccepted:" << event->isAccepted()
            << "spontaneous:" << event->spontaneous();
    return true;
}

void testPlugin::setModName(const QString modName)
{
    this->modName = modName;
}

void    testPlugin::setModVersion(const QString modVersion)
{
    this->modVersion = modVersion;
}

void    testPlugin::setModRequired(const QString name)
{
    modRequired << name;
}

void    testPlugin::setModConflicts(const QString name)
{
    modConflicts << name;
}

void    testPlugin::setExports(const QString name)
{
    exports << name;
}

void    testPlugin::setModRecommended(const QString name)
{
    modRecommended << name;
}

QString   testPlugin::getName() const
{
    return modName;
}

QString   testPlugin::getVersion() const
{
    return modVersion;
}

QStringList   testPlugin::getPluginsConflicts() const
{
    return modConflicts;
}

QStringList   testPlugin::getPluginsRequired() const
{
    return modRequired;
}

QStringList   testPlugin::getPluginsRecommended() const
{
    return modRecommended;
}

QStringList   testPlugin::getExports() const
{
    return exports;
}

