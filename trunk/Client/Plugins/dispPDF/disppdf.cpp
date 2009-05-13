#include <QtCore/qplugin.h>

#include "../../NetworkReceiveEvent.h"
#include "../../UnloadPluginEvent.h"
#include "../../LoadPluginEvent.h"

#include "disppdf.h"

Q_EXPORT_PLUGIN2(dispPDF, DispPDF)

DispPDF::DispPDF()
{
}

const QByteArray        DispPDF::getName() const
{
    return name;
}

const QByteArray        DispPDF::getVersion() const
{
    return version;
}

QStringList             DispPDF::getPluginsConflicts() const
{
    return pluginsConflicts;
}


QStringList             DispPDF::getPluginsRequired() const
{
    return plugindRequired;
}

QStringList           DispPDF::getPluginsRecommended() const
{
    return pluginsRecommended;
}

//QStringList           getExports();

bool    DispPDF::event(QEvent *event)
{
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

bool    DispPDF::eventHandlerLoad(QEvent *event)
{
    return true;
}

bool    DispPDF::eventHandlerUnload(QEvent *event)
{
    return true;
}
