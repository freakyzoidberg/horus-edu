#include "PdfController.h"

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
#include "../../PdfDisplayer/IPdfRendering.h"

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

QWidget* PdfController::createDocumentWidget(QWidget *parent, ILessonDocument *document)
{
    IPdfRendering   *pdf;
    int             index = 0;
    bool            ok;
    int             x, y, w, h;
    int             page;
    QString         fileName;
    QRectF          *rect;
    QImage          *image;

    qDebug() << "Nuclear launch detected.";

    if (document->getType() != this->getSupportedType())
    {
        qDebug() << "[Plugin PdfController] Type error:";
        qDebug() << "\tThe type of your IObject is" << document->getType();
        qDebug() << "\tThe controller PdfController handle " << this->getSupportedType() << " type.";
    }

    pdf = this->pluginManager->findPlugin<IPdfRendering *>();
    if (!pdf)
    {
        qDebug() << "IPdfRendering not found";
        return NULL;
    }
    fileName = document->getParameters().value("name").toString();
    x = document->getParameters()["x"].toInt();
    y = document->getParameters()["y"].toInt();
    w = document->getParameters()["w"].toInt();
    h = document->getParameters()["h"].toInt();
    page = document->getParameters()["page"].toInt();
    rect = new QRectF(x, y, h, w);

    image = pdf->PdfDisplayerDoc(fileName, page, rect, 0);
    if (!image)
    {
       qDebug() << "Call the shot";
       delete rect;
       return NULL;
    }

   // QImage disp = image->scaled(object->getSize().width(),
     //                           object->getSize().height());
        QPixmap pix = QPixmap::fromImage(*image);

        if (label)
            delete label;

        label = new QLabel(parent);
        label->setPixmap(pix);
        //object->getWidget()->show();
//label->show();

        delete rect;
        delete image;

    /*
  for (index = 0; index < requieredFiles.count(); ++index)
    {
        qDebug() << "I dont have time to *BLEEP* around";
        QVariant        var(requieredFiles.at(index));
        QString         fileName = conf.toString() + "/" + var.toString();
        QStringList     splitParams = parameters.at(index).split(";");
        int             page;
        float           topX, topY, height, width;
        QRectF  *rect;
        QImage  *image;

        page = splitParams.at(0).toInt(&ok);
        if (!ok)
        {
            qDebug() << "Invalid conversion";
            delete rect;
            return ;
        }
        topX = splitParams.at(1).toFloat(&ok);
        if (!ok)
        {
            qDebug() << "Invalid conversion";
            delete rect;
            return ;
        }
        topY = splitParams.at(2).toFloat(&ok);
        if (!ok)
        {
            qDebug() << "Invalid conversion";
            delete rect;
            return ;
        }
        height = splitParams.at(3).toFloat(&ok);
        if (!ok)
        {
            qDebug() << "Invalid conversion";
            delete rect;
            return ;
        }
        width = splitParams.at(4).toFloat(&ok);
        if (!ok)
        {
            qDebug() << "Invalid conversion";
            delete rect;
            return ;
        }
        qDebug() << "true file name:" << fileName;
        rect = new QRectF(topX, topY, height, width);



    } */

    return label;
}
