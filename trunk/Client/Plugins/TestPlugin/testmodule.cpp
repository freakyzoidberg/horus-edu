#include <QtCore/qplugin.h>
#include <QDebug>
#include <iostream>
#include "testmodule.h"

#include "../../ClientEvents.h"

Q_EXPORT_PLUGIN2(testModule, testPlugin)

extern QEvent::Type ClientEvents::NetworkReceiveEvent;
extern QEvent::Type ClientEvents::UnloadPluginEvent;
extern QEvent::Type ClientEvents::LoadPluginEvent;
extern QEvent::Type ClientEvents::StartEvent;

testPlugin::testPlugin()
{
    std::cout << "module testPlugin loaded. HAHAHAHA" << std::endl;
    setModRecommended("NotAModule.so");
    pNetwork = new PluginNetwork();
}

testPlugin::~testPlugin()
{
    std::cout << "module testPlugin unloaded." << std::endl;
    delete pNetwork;
}

bool    testPlugin::event(QEvent *event)
{
    if (event->type() == ClientEvents::StartEvent)
        qDebug() << "Event received";

    if (event->type() == ClientEvents::NetworkReceiveEvent)
    {
        event->accept();        
        return true; //pNetwork->eventHandler(event);
    }
    else if (event->type() == ClientEvents::LoadPluginEvent)
    {
        event->accept();
        return eventHandlerLoad(event);
    }
    else if (event->type() == ClientEvents::UnloadPluginEvent)
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

void testPlugin::setModName(const QByteArray modName)
{
    this->modName = modName;
}

void    testPlugin::setModVersion(const QByteArray modVersion)
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

const QByteArray   testPlugin::getName() const
{
    return modName;
}

const QByteArray   testPlugin::getVersion() const
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
