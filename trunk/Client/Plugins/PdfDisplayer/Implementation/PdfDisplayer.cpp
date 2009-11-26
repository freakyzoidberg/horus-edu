/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "PdfDisplayer.h"

#include "Plugin.h"
#include <QDebug>
#include <QEvent>
#include <QFileInfo>
#include <QMapIterator>
#include <QVariant>
#include <QList>

#include "../../../../Common/FileData.h"

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

//bool    PdfDisplayer::PluginEventHandler(QEvent *event)
//{
//    QVariant    data;
//    QList<QVariant> dataList;
//    quint32     fileId;
//    int         page;
//
//    PluginEvent *pe = static_cast<PluginEvent *>(event);
//    data = pe->pack.data;
//
//    dataList = data.toList();
//    fileId = dataList.at(0).toInt();
//    page = dataList.at(1).toInt();
//    QRectF  *rect = new QRectF(dataList.at(2).toRectF());
//    QString fileName(dataList.at(3).toString());
//    if (fileName.isEmpty() || fileName.isNull())
//        PdfDisplayerDoc(fileName, page, rect, fileId);
//    else
//        PdfDisplayerDoc(fileId, page, rect);
//    return true;
//}

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

QImage    *PdfDisplayer::PdfDisplayerDoc(const QString & fileName, int page)
{
    QFileInfo    filePath(fileName);
    QMap<quint32, IPdfFile *>::iterator it;

    if (!filePath.isAbsolute())
        if (!filePath.makeAbsolute())
        {
            qDebug() << "Cannot use the absolute path of the pdf file";
            return NULL;
        }
    quint32 fileId = fileName.toInt();

    fileId = 1;

    if ((it = pdfFiles->find(fileId)) == pdfFiles->end())
        it = pdfFiles->insert(fileId, new PdfFile(filePath.filePath()));
    return it.value()->render(page);
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
