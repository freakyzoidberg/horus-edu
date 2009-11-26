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
#include "PdfController.h"
#include "../editorpdf.h"

#include <QFileDialog>
#include <QDebug>
#include <QtCore/qplugin.h>
#include <QStringList>
#include <QRectF>
#include <QVariant>
#include <QSettings>
#include <QDir>
#include <QPixmap>
#include <QLabel>

#include "../../../../Common/PluginManager.h"

PdfController::PdfController()
{
    qDebug() << "All right, bring it on!";
    label = NULL;
}

PdfController::~PdfController()
{
    qDebug() << "Oh, is that it?";
}

const QString    PdfController::pluginName() const
{
    return "PdfController";
}

const QString    PdfController::pluginVersion() const
{
    return "0.2";
}

//void    PdfController::showObject(ILesson::IPage::IObject *object)
//{

//}
//
//void    PdfController::activateObject(ILesson::IPage::IObject *object)
//{
//
//}
//
//void    PdfController::hideObject(ILesson::IPage::IObject *object)
//{
//        if (label)
//            delete label;
//        object->getWidget()->hide();
//}
//
//void    PdfController::configureObject(ILesson::IPage::IObject *object)
//{
// //build the configuration string:
//}

const QString  PdfController::getSupportedType() const
{
    return ("Pdf");
}

QWidget* PdfController::createDocumentWidget(ILessonDocument *document)
{
    int         x, y, w, h;
    int         fileId;

     /*if (document->getType() != this->getSupportedType())
    {
        qDebug() << "[Plugin PdfController] Type error:";
        qDebug() << "\tThe type of your IObject is" << document->getType();
        qDebug() << "\tThe controller PdfController handle " << this->getSupportedType() << " type.";
    }*/

    //fileId = document->getParameters().value("id").toInt();
    /* x = document->getParameters()["x"].toInt();
    y = document->getParameters()["y"].toInt();
    w = document->getParameters()["w"].toInt();
    h = document->getParameters()["h"].toInt(); */


    //page = document->getParameters()["page"].toInt();
    fileId = 19;
    page = 10;
    x = y = w = h = 100;
    rect = new QRectF(x, y, h, w);
	data = pluginManager->findPlugin<FileDataPlugin*>()->file(fileId);
    this->connect(data, SIGNAL(downloaded()), this, SLOT(dl()));
    label = new QLabel("Loading pdf...");

   // if (data->isDownloaded())
        dl();

    return label;
}

void    PdfController::dl()
{
    qDebug() << "file downloaded";
    QString         fileName;
    QImage          *image;

    pdf = this->pluginManager->findPlugin<IPdfRendering *>();
    if (!pdf)
    {
        qDebug() << "IPdfRendering not found";
        return ;
    }

    fileName = data->file()->fileName();
    image = pdf->PdfDisplayerDoc(fileName, page, rect, 0);
    if (!image)
    {
       qDebug() << "Call the shot";
       delete rect;
       return ;
    }

    //QImage disp = image->scaled(w, h);
    QPixmap pix = QPixmap::fromImage(*image);

    label->setPixmap(pix);
    delete rect;
    delete image;
}

void    PdfController::reload()
{
    QString     fileName;
    QImage      *image;

    pdf = this->pluginManager->findPlugin<IPdfRendering *>();
    if (!pdf)
    {
        qDebug() << "IPdfRendering not found";
        return ;
    }

    fileName = data->file()->fileName();
    image = pdf->PdfDisplayerDoc(fileName, page, rect, 0);
    if (!image)
    {
       qDebug() << "Call the shot";
       delete rect;
       return ;
    }

    //QImage disp = image->scaled(w, h);
    QPixmap pix = QPixmap::fromImage(*image);

    label->setPixmap(pix);
    delete rect;
    delete image;
}

QWidget      *PdfController::editDocument(QFile *metadata, ILessonDocument *doc)
{
    QString     fileName;
    QImage      *image;
    EditorPdf    *pdfEdit = new EditorPdf(parent, doc);

    pdf = this->pluginManager->findPlugin<IPdfRendering *>();
    if (!pdf)
    {
        qDebug() << "IPdfRendering not found";
        return NULL;
    }
    int page = doc->getParameters().value("page").toInt();
    fileName = metadata->fileName();
    image = pdf->PdfDisplayerDoc(fileName, page);

    qDebug() << "page to display:" << page;

    if (!image)
    {
       qDebug() << "Call the shot";
       return NULL;
    }

    QPixmap pix = QPixmap::fromImage(*image);

    parent->setGeometry(20, 20, 500, 500);
    pdfEdit->setPixmap(pix);
    return pdfEdit;
}
