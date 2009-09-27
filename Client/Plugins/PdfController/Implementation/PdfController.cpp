#include "PdfController.h"

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

QWidget* PdfController::createDocumentWidget(IItems *parent, ILessonDocument *document)
{
    int         x, y, w, h;
    int         fileId;

    if (document->getType() != this->getSupportedType())
    {
        qDebug() << "[Plugin PdfController] Type error:";
        qDebug() << "\tThe type of your IObject is" << document->getType();
        qDebug() << "\tThe controller PdfController handle " << this->getSupportedType() << " type.";
    }

    fileId = document->getParameters().value("id").toInt();
    x = document->getParameters()["x"].toInt();
    y = document->getParameters()["y"].toInt();
    w = document->getParameters()["w"].toInt();
    h = document->getParameters()["h"].toInt();
    page = document->getParameters()["page"].toInt();
    rect = new QRectF(x, y, h, w);
    data = pluginManager->findPlugin<FileDataPlugin*>()->getFile(fileId);
    this->connect(data, SIGNAL(downloaded()), this, SLOT(dl()));
    label = new QLabel("Loading pdf...", parent);

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


void         PdfController::clean(IItems *widget)
{

}

void         PdfController::resizeWidget(IItems *widget)
{

}

QWidget      *PdfController::editDocument(QFile *metadata, QWidget *parent, ILessonDocument *)
{
    QString     fileName;
    QImage      *image;

    pdf = this->pluginManager->findPlugin<IPdfRendering *>();
    if (!pdf)
    {
        qDebug() << "IPdfRendering not found";
        return NULL;
    }

    fileName = data->file()->fileName();
    image = pdf->PdfDisplayerDoc(fileName, page);
    if (!image)
    {
       qDebug() << "Call the shot";
       delete rect;
       return NULL;
    }

    //QImage disp = image->scaled(w, h);
    QPixmap pix = QPixmap::fromImage(*image);

    label->setPixmap(pix);
    delete rect;
    delete image;

    return label;
}
