#include <QtCore/qplugin.h>
#include "../../ClientEvents.h"
#include "../../IClient.h"
#include "PageDisplayer.h"

extern QEvent::Type ClientEvents::LoadPluginEvent;
extern QEvent::Type ClientEvents::UnloadPluginEvent;

Q_EXPORT_PLUGIN2(pageDisplayerModule, PageDisplayer)

PageDisplayer::PageDisplayer()
{
    this->modName = "PageDisplayer";
    this->modVersion = "1.0";
    qDebug() << "module PageDisplayer loaded.";
}

PageDisplayer::~PageDisplayer()
{
    qDebug() << "module PageDisplayer unloaded.";
}

const QByteArray    PageDisplayer::getName() const
{
    return this->modName;
}

const QByteArray    PageDisplayer::getVersion() const
{
    return this->modVersion;
}

QStringList         PageDisplayer::getPluginsConflicts() const
{
    return this->modConflicts;
}

QStringList         PageDisplayer::getPluginsRequired() const
{
    return this->modRequired;
}

QStringList         PageDisplayer::getPluginsRecommended() const
{
    return this->modRecommended;
}

bool    PageDisplayer::event(QEvent *event)
{
    if (event->type() == ClientEvents::LoadPluginEvent)
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

bool    PageDisplayer::eventHandlerLoad(QEvent *event)
{
    qDebug()  << "Handling event loadModule"
            << "isAccepted:"    << event->isAccepted()
            << "spontaneous:"   << event->spontaneous();
    return true;
}

bool    PageDisplayer::eventHandlerUnload(QEvent *event)
{
    qDebug()  << "Handling event UnlodModule"
            << "isAccepted:" << event->isAccepted()
            << "spontaneous:" << event->spontaneous();
    return true;
}
