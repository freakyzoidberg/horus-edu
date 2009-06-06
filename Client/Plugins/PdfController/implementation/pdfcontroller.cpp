#include <QDebug>
#include <QtCore/qplugin.h>
#include <QStringList>
#include <QRectF>
#include <QVariant>
#include <QSettings>
#include <QDir>
#include <QPixmap>
#include <QLabel>

#include <ClientEvents.h>
#include <IClient.h>
#include "../../dispPDF/IPdfRendering.h"
#include "pdfcontroller.h"

extern QEvent::Type ClientEvents::UnloadPluginEvent;
extern QEvent::Type ClientEvents::LoadPluginEvent;
extern QEvent::Type ClientEvents::PluginEvent;

Q_EXPORT_PLUGIN2(pdfcontroller, pdfController)

pdfController::pdfController()
{
    qDebug() << "All right, bring it on!";
    supportedType = "Pdf";
    label = NULL;
}

pdfController::~pdfController()
{
    qDebug() << "Oh, is that it?";
}

const QByteArray    pdfController::getName() const
{
    return "PdfController";
}

const QByteArray    pdfController::getVersion() const
{
    return version;
}

QStringList     pdfController::getPluginsConflicts() const
{
    return pluginsConflicts;
}


QStringList     pdfController::getPluginsRequired() const
{
    return plugindRequired;
}

QStringList     pdfController::getPluginsRecommended() const
{
    return pluginsRecommended;
}

//QStringList           getExports();

bool    pdfController::event(QEvent *event)
{
    if  (event->type() == ClientEvents::PluginEvent)
    {
        event->accept();
        return true;
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

bool    pdfController::eventHandlerLoad(QEvent *event)
{
    return true;
}

bool    pdfController::eventHandlerUnload(QEvent *event)
{
    return true;
}

void    pdfController::showObject(ILesson::IPage::IObject *object)
{
    QList<unsigned int>     requieredFiles = object->getRequiredFiles();
    QStringList             parameters = object->getParameters().split(":");
    IClientPlugin           *clientPlugin;
    IPdfRendering           *pdf;
    int             index = 0;
    bool            ok;

    QSettings   settings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat);
    QVariant conf = settings.value("TmpDir", QVariant(QDir::homePath() + "/.Horus/Plugins/tmp/"));
    qDebug() << "FILLLLEEENNNAAEMMMM:" << conf.toString();

    qDebug() << "Nuclear launch detected.";

    if (object->getType() != this->getSupportedType())
    {
        qDebug() << "[Plugin pdfcontroller] Type error:";
        qDebug() << "\tThe type of your IObject is" << object->getType();
        qDebug() << "\tThe controller pdfcontroller handle " << this->getSupportedType() << " type.";
    }

    clientPlugin = this->client->getPlugin("dispPDF");
    if (!clientPlugin)
    {
        qDebug() << "Nuclear launch detected.";
        return ;
    }
    pdf = qobject_cast<IPdfRendering *>(clientPlugin);
    if (!pdf)
    {
        qDebug() << "ta mere";
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

void    pdfController::activateObject(ILesson::IPage::IObject *object)
{

}

void    pdfController::hideObject(ILesson::IPage::IObject *object)
{
        if (label)
            delete label;
        object->getWidget()->hide();
}

void    pdfController::configureObject(ILesson::IPage::IObject *object)
{
 //build the configuration string:
}

const QString&  pdfController::getSupportedType() const
{
    return supportedType;
}
