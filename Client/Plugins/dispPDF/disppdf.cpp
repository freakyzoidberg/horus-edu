#include <QtCore/qplugin.h>
#include <QDebug>

#include "../../ClientEvents.h"

#include "disppdf.h"

extern QEvent::Type ClientEvents::NetworkReceiveEvent;
extern QEvent::Type ClientEvents::UnloadPluginEvent;
extern QEvent::Type ClientEvents::LoadPluginEvent;

Q_EXPORT_PLUGIN2(dispPDF, DispPDF)

DispPDF::DispPDF()
{
    qDebug() << "[plugin dispPDF] : initialisation";

    pNetwork = new DispPDFNetwork();
    name = PLUGIN_NAME; /* dispPDF */
    version = PLUGIN_VERSION; /* 1.0 */
}

DispPDF::~DispPDF()
{
    if (pNetwork != NULL)
        delete pNetwork;
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
    if (event->type() == ClientEvents::NetworkReceiveEvent)
    {
        event->accept();
        return pNetwork->eventHandler(event);
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

bool    DispPDF::eventHandlerLoad(QEvent *event)
{
    return true;
}

bool    DispPDF::eventHandlerUnload(QEvent *event)
{
    return true;
}

void    DispPDF::dispPDFDoc(const QString & fileName)
{
 // check if the file is already in the vector
  /*
    if no add it
    else do something
    */
}
