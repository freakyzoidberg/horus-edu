#include <QtCore/qplugin.h>
#include <QDebug>
#include <QFileInfo>
#include <QMapIterator>

#include <ClientEvents.h>

#include <disppdf.h>
#include <pdfRendering.h>

extern QEvent::Type ClientEvents::NetworkReceiveEvent;
extern QEvent::Type ClientEvents::UnloadPluginEvent;
extern QEvent::Type ClientEvents::LoadPluginEvent;

Q_EXPORT_PLUGIN2(dispPDF, DispPDF)

DispPDF::DispPDF()
{
    qDebug() << "[plugin dispPDF] : initialisation";

    //pNetwork = new DispPDFNetwork();
    name = PLUGIN_NAME; /* dispPDF */
    version = PLUGIN_VERSION; /* 1.0 */
    pdfFiles = new QMap<QString, PdfRendering *>;
}

DispPDF::~DispPDF()
{
    QMap<QString, PdfRendering *>::iterator   it, itend;

    //if (pNetwork != NULL)
      //  delete pNetwork;
    if (pdfFiles && !pdfFiles->empty())
    {
        itend = pdfFiles->end();
        for (it = pdfFiles->begin(); it != itend; ++it)
        {
            //if (it.value() == NULL)
                qDebug() << "houlalala";
            delete it.value();
            qDebug() << "houlalali";
           // pdfFiles->erase(it);
        }
    }
    delete pdfFiles;
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
        //return pNetwork->eventHandler(event);
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

bool    DispPDF::dispPDFDoc(const QString & fileName)
{
    QFileInfo    filePath(fileName);
    QMap<QString, PdfRendering *>::iterator it;

    if (!filePath.isAbsolute())
        if (!filePath.makeAbsolute())
        {
            qDebug() << "Cannot use the absolute path of the Metafile";
            return false;
        }

    if ((it = pdfFiles->find(filePath.filePath())) == pdfFiles->end())
    {
        qDebug() << "open new course";
        it = pdfFiles->insert(filePath.filePath(),
                               new PdfRendering(filePath.filePath()));

    }
    //it.value()->render();
    // access
    return true;
}

const QMap<QString, PdfRendering *>    *DispPDF::getAllPdfFiles() const
{
    return pdfFiles;
}

void    DispPDF::closeCourse(const QString &fileName)
{
    QFileInfo    filePath(fileName);

    if (!filePath.isAbsolute())
        if (!filePath.makeAbsolute())
        {
            qDebug() << "Cannot use the absolute path of the pdf file";
            return ;
        }

    delete pdfFiles->value(filePath.filePath());
    pdfFiles->remove(filePath.filePath());
}
