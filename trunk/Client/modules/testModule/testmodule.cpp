#include <QtCore/qplugin.h>

#include "testmodule.h"

Q_EXPORT_PLUGIN2("testPlugin", TestModule)

TestModule::TestModule()
{
}

bool    TestModule::event(QEvent *event)
{
    if (event->type() == NetworkReceiveEvent)
    {
        pNetwork    network(*event);
        return network.handler();
    }
    else if (event->type() == LoadPluginEvent)
        return eventHandlerLoad();
    else if (event->type() == UnloadPluginEvent)
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

void    TestModule::setModRequired(const QString name, const QString version)
{

}

void    TestModule::setModConflicts(const QString name, const QString version)
{

}

void    TestModule::setModRecommended(const QString name, const QString version)
{

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

