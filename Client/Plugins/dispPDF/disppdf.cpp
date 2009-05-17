#include <QtCore/qplugin.h>
#include <QDebug>
#include <QFileInfo>

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
    QFileInfo    filePath(fileName);
    QMap<QString, PdfRendering::PdfRendering *>::iterator it;

    if (!filePath.isAbsolute())
        if (!filePath.makeAbsolute())
        {
            qDebug() << "Cannot use the absolute path of the PDF file";
            return ;
        }

    if ((it = renderPdf->find(filePath.filePath())) == renderPdf->end())
        it = renderPdf->insert(filePath.filePath(), new PdfRendering(filePath.filePath()));

    it.value()->render();
    // access
}

const QMap<QString, PdfRendering *>    *DispPDF::getRenderPdf() const
{
    return renderPdf;
}
