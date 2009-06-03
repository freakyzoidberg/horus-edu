#include <QtCore/qplugin.h>
#include <QDebug>
#include <QFileInfo>
#include <QMapIterator>

#include <ClientEvents.h>

#include <disppdf.h>
#include <pdfRendering.h>

extern QEvent::Type ClientEvents::UnloadPluginEvent;
extern QEvent::Type ClientEvents::LoadPluginEvent;

Q_EXPORT_PLUGIN2(dispPDF, DispPDF)

DispPDF::DispPDF()
{
    qDebug() << "[plugin dispPDF] : initialisation";

    name = PLUGIN_NAME; /* dispPDF */
    version = PLUGIN_VERSION; /* 1.0 */
    pdfFiles = new QMap<QString, PdfRendering *>;
}

DispPDF::~DispPDF()
{
    QMap<QString, PdfRendering *>::iterator   it, itend;

    if (pdfFiles && !pdfFiles->empty())
    {
        itend = pdfFiles->end();
        for (it = pdfFiles->begin(); it != itend; ++it)
            delete it.value();
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

bool    DispPDF::eventHandlerLoad(QEvent *event)
{
    return true;
}

bool    DispPDF::eventHandlerUnload(QEvent *event)
{
    return true;
}

QImage    *DispPDF::dispPDFDoc(int fileId, int page,
                            QRectF *partToDisplay)
{
    QString fileName;

    //fileName = File->getNameById(fileId);
    return dispPDFDoc(fileName, page, partToDisplay);
}

QImage    *DispPDF::dispPDFDoc(const QString & fileName, int page,
                               QRectF *partToDisplay)
{
    QFileInfo    filePath(fileName);
    QMap<QString, PdfRendering *>::iterator it;

    if (!filePath.isAbsolute())
        if (!filePath.makeAbsolute())
        {
            qDebug() << "Cannot use the absolute path of the pdf file";
            return NULL;
        }

    //search if the pdf file is already open, if not add it in the map
    if ((it = pdfFiles->find(filePath.filePath())) == pdfFiles->end())
        it = pdfFiles->insert(filePath.filePath(),
                               new PdfRendering(filePath.filePath()));

    return it.value()->render(page, partToDisplay);
}

const QMap<QString, PdfRendering *>    *DispPDF::getAllPdfFiles() const
{
    return pdfFiles;
}

void    DispPDF::closePdfFile(int fileId)
{
    QString fileName;

    //fileName = File->getNameById(fileId);
    closePdfFile(fileName);
}

void    DispPDF::closePdfFile(const QString &fileName)
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
