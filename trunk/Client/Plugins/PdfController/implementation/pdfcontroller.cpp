#include <QDebug>
#include <QtCore/qplugin.h>
#include <QStringList>
#include <QRectF>
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
     qDebug() << "jsuis dans le controle";

    /*QMap<QString, int>              requieredFiles = object->getRequiredFiles();
    QMap<QString, int>::iterator    it, itend = requieredFiles.end();*/

    IClientPlugin   *clientPlugin;
    IPdfRendering   *pdf;
    QStringList     parameters = object->getParameters().split(":");
    int             index;
    bool            ok;

    /*
    if (object->getType() != this->getSupportedType())
    {
        qDebug() << "[Plugin pdfcontroller] Type error:";
        qDebug() << "\tThe type of your IObject is" << object->getType();
        qDebug() << "\tThe controller pdfcontroller handle " << this->getSupportedType() << " type.";
    }

    if (parameters.count() != requieredFiles.count())
    {
        qDebug() << "Error parsing params string";
        return ;
    }
    */
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

   // for (it = requieredFiles.begin(), index = 0; it != itend; ++it, ++index)
    {
        qDebug() << "I dont have time to *BLEEP* around";
        //parse parameters
        QString fileName; // = it.key();
        //QStringList splitParams = parameters.at(index).split(";");
        int     page = 10;
        float   topX = 100, topY = 100, height = 50, width = 50;
        QRectF  *rect;
        QImage  *image;

        /*
        if (splitParams.size() != 5)
        {
            qDebug() << "Error while parsing params string";
            continue ;
        }

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
        } */

        rect = new QRectF(topX, topY, height, width);
        image = pdf->dispPDFDoc("adobe_supplement_iso32000.pdf", page, rect, 0);
        if (!image)
        {
            qDebug() << "Call the shot";
            delete rect;
            return ;
        }

        QImage disp = image->scaled(object->getSize().width(),
                                    object->getSize().height());
        qDebug() << "try to display";
        QPixmap pix = QPixmap::fromImage(*image);
        QLabel *label = new QLabel(object->getWidget()); //
        label->setPixmap(pix);
        //label->show();
        object->getWidget()->show();
        delete rect;
        delete image;
        //break ;
    }
}

void    pdfController::activateObject(ILesson::IPage::IObject *object)
{

}

void    pdfController::hideObject(ILesson::IPage::IObject *object)
{
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
