#include <QtCore/qplugin.h>
#include <QDebug>
#include <QFileInfo>
#include <QMapIterator>
#include <QVariant>
#include <QList>

#include <ClientEvents.h>

#include <disppdf.h>
#include <IPdfFile.h>

#include <IFile.h>

extern QEvent::Type ClientEvents::UnloadPluginEvent;
extern QEvent::Type ClientEvents::LoadPluginEvent;
extern QEvent::Type ClientEvents::PluginEvent;

Q_EXPORT_PLUGIN2(dispPDF, DispPDF)

DispPDF::DispPDF()
{
    qDebug() << "[plugin dispPDF] : initialisation";

    name = PLUGIN_NAME; /* dispPDF */
    version = PLUGIN_VERSION; /* 1.0 */
    pdfFiles = new QMap<quint32, IPdfFile *>;
}

DispPDF::~DispPDF()
{
    QMap<quint32, IPdfFile *>::iterator   it, itend;

    if (!pdfFiles->empty())
    {
        itend = pdfFiles->end();
        for (it = pdfFiles->begin(); it != itend; ++it)
            delete it.value();
    }
    delete pdfFiles;
}

const QByteArray    DispPDF::getName() const
{
    return name;
}

const QByteArray    DispPDF::getVersion() const
{
    return version;
}

QStringList     DispPDF::getPluginsConflicts() const
{
    return pluginsConflicts;
}


QStringList     DispPDF::getPluginsRequired() const
{
    return plugindRequired;
}

QStringList     DispPDF::getPluginsRecommended() const
{
    return pluginsRecommended;
}

//QStringList           getExports();

bool    DispPDF::event(QEvent *event)
{
    qDebug() << "Incoming transmission.";
    if  (event->type() == ClientEvents::PluginEvent)
    {
        qDebug() << "I read ya... Sir!";
        event->accept();
        return PluginEventHandler(event);
    }
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

bool    DispPDF::PluginEventHandler(QEvent *event)
{
    QVariant    data;
    QList<QVariant> dataList;
    quint32     fileId;
    int         page;

    PluginEvent *pe = static_cast<PluginEvent *>(event);
    data = pe->pack.data;

    dataList = data.toList();
    fileId = dataList.at(0).toInt();
    page = dataList.at(1).toInt();
    QRectF  *rect = new QRectF(dataList.at(2).toRectF());
    QString fileName(dataList.at(3).toString());
    if (fileName.isEmpty() || fileName.isNull())
        dispPDFDoc(fileName, page, rect, fileId);
    else
        dispPDFDoc(fileId, page, rect);
    return true;
}

bool    DispPDF::eventHandlerLoad(QEvent *event)
{
    return true;
}

bool    DispPDF::eventHandlerUnload(QEvent *event)
{
    return true;
}

QImage    *DispPDF::dispPDFDoc(quint32 fileId, int page,
                               QRectF *partToDisplay)
{
    QString fileName;
    IFile   *file;

    file = fileManager->getFile(fileId);
    if (!file)
       return NULL;
    fileName = file->getLocalFileName();
    return dispPDFDoc(fileName, page, partToDisplay, fileId);
}

QImage    *DispPDF::dispPDFDoc(const QString & fileName, int page,
                               QRectF *partToDisplay, int fileId)
{
    QFileInfo    filePath(fileName);
    QMap<quint32, IPdfFile *>::iterator it;

    if (!filePath.isAbsolute())
        if (!filePath.makeAbsolute())
        {
            qDebug() << "Cannot use the absolute path of the pdf file";
            return NULL;
        }

    //if the file doesn't exist recup it using the method of the IFile * interface
    /*if (!filePath.exists())
    {
        bool  success;

        if (fileId != -1)
            success = file->needFile(fileId);
        else
            success = file->needFile(fileName);
        if (!success)
            return NULL;
    }

    if (fileId == -1)
        fileId = file->getFileIdByName(filePath.filePath());
    else if (fileName.isEmpty() || fileName.isNull())
        fileName = file->getNameById(fileId);*/

    /*
       search if the pdf file is already in the map, if not add it in the map
       and return the iterator.
    */
    if ((it = pdfFiles->find(fileId)) == pdfFiles->end())
        it = pdfFiles->insert(fileId, new PdfFile(filePath.filePath()));
    return it.value()->render(page, partToDisplay);
}

const QMap<quint32, IPdfFile *>    *DispPDF::getAllPdfFiles() const
{
    return pdfFiles;
}

void    DispPDF::closePdfFile(int fileId)
{
    delete pdfFiles->value(fileId);
    pdfFiles->remove(fileId);
}
