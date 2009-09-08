#include "PdfDisplayer.h"

#include "Plugin.h"
#include <QDebug>
#include <QEvent>
#include <QFileInfo>
#include <QMapIterator>
#include <QVariant>
#include <QList>

#include "../../../../Common/FileData.h"
#include "../../../ClientEvents.h"

#include "../IPdfFile.h"

PdfDisplayer::PdfDisplayer()
{
    qDebug() << "[plugin PdfDisplayer] : initialisation";
    pdfFiles = new QMap<quint32, IPdfFile *>;
}

PdfDisplayer::~PdfDisplayer()
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

const QString    PdfDisplayer::pluginName() const
{
    return ("PdfDisplayer");
}

const QString    PdfDisplayer::pluginVersion() const
{
    return ("1.1");
}

bool    PdfDisplayer::event(QEvent *event)
{
    qDebug() << "Incoming transmission.";
    /*if  (event->type() == ClientEvents::PluginEvent)
    {
        qDebug() << "I read ya... Sir!";
        event->accept();
        return PluginEventHandler(event);
    } */
    return QObject::event(event);
}

bool    PdfDisplayer::PluginEventHandler(QEvent *event)
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
        PdfDisplayerDoc(fileName, page, rect, fileId);
    else
        PdfDisplayerDoc(fileId, page, rect);
    return true;
}

QImage    *PdfDisplayer::PdfDisplayerDoc(quint32 fileId, int page,
                               QRectF *partToDisplay)
{
    QString fileName;
    FileData   *file;

    file = 0;//fileManager->getFile(fileId); TODO: use filemanager
    if (!file)
       return 0;
    fileName = "";//file->getLocalFileName();
    return PdfDisplayerDoc(fileName, page, partToDisplay, fileId);
}

QImage    *PdfDisplayer::PdfDisplayerDoc(const QString & fileName, int page,
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

const QMap<quint32, IPdfFile *>    *PdfDisplayer::getAllPdfFiles() const
{
    return pdfFiles;
}

void    PdfDisplayer::closePdfFile(int fileId)
{
    delete pdfFiles->value(fileId);
    pdfFiles->remove(fileId);
}
