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
#include "../../dispPDF/IPdfRendering.h"

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

void    PdfController::showObject(ILesson::IPage::IObject *object)
{
    QList<unsigned int>     requieredFiles = object->getRequiredFiles();
    QStringList             parameters = object->getParameters().split(":");
    IPdfRendering           *pdf;
    int             index = 0;
    bool            ok;

    QSettings   settings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat);
    QVariant conf = settings.value("TmpDir", QVariant(QDir::homePath() + "/.Horus/Plugins/tmp/"));
    qDebug() << "FILLLLEEENNNAAEMMMM:" << conf.toString();

    qDebug() << "Nuclear launch detected.";

    if (object->getType() != this->getSupportedType())
    {
        qDebug() << "[Plugin PdfController] Type error:";
        qDebug() << "\tThe type of your IObject is" << object->getType();
        qDebug() << "\tThe controller PdfController handle " << this->getSupportedType() << " type.";
    }
	pdf = this->pluginManager->findPlugin<IPdfRendering *>();
    if (!pdf)
    {
        qDebug() << "IPdfRendering not found";
        return ;
    }

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
        image = pdf->dispPDFDoc(fileName, page, rect, 0);
        if (!image)
        {
            qDebug() << "Call the shot";
            delete rect;
            return ;
        }

        QImage disp = image->scaled(object->getSize().width(),
                                    object->getSize().height());
        QPixmap pix = QPixmap::fromImage(*image);

        if (label)
            delete label;

        label = new QLabel(object->getWidget());
        label->setPixmap(pix);
        object->getWidget()->show();
        delete rect;
        delete image;
    }
}

void    PdfController::activateObject(ILesson::IPage::IObject *object)
{

}

void    PdfController::hideObject(ILesson::IPage::IObject *object)
{
        if (label)
            delete label;
        object->getWidget()->hide();
}

void    PdfController::configureObject(ILesson::IPage::IObject *object)
{
 //build the configuration string:
}

const QString  PdfController::getSupportedType() const
{
    return ("Pdf");
}
