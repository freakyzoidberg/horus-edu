#include <QtCore/qplugin.h>

#include "testmodule.h"

Q_EXPORT_PLUGIN2("testPlugin", TestModule)

TestModule::TestModule()
{
}

bool    TestModule::event(QEvent *event)
{
    if (event->type() == QEvent::None)
        //NetworkReceiveEvent)
    {
        pNetwork = new PluginNetwork(event);
        return pNetwork->handler();
    }
    else if (event->type() == QEvent::None)
             //LoadPluginEvent)
        return eventHandlerLoad();
    else if (event->type() == QEvent::None)
             //UnloadPluginEvent)
        return eventHandlerUnload();
    return QObject::event(event);
}

bool    TestModule::eventHandlerLoad()
{
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

