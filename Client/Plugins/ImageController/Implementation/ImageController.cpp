#include "ImageController.h"

#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QFileDialog>
#include <QPushButton>

const QString    ImageController::pluginName() const
{
    return ("imageController");
}

const QString    ImageController::pluginVersion() const
{
    return ("0.2");
}

const QString      ImageController::getSupportedType() const
{
    return ("image");
}

QWidget*            ImageController::createDocumentWidget(ILessonDocument *document)
{
        qDebug() << "doc:" << document;




    int fileId = 15;
    //fileId = document->getParameters().value("id").toInt();
    //fileId = document->getId();
    qDebug() << "file id:" << fileId;

   data = pluginManager->findPlugin<FileDataPlugin*>()->file(fileId);
    this->connect(data, SIGNAL(downloaded()), this, SLOT(dl()));

  //  if (document->getType() != this->getSupportedType())
    {
        qDebug() << "[Plugin ImageController] Type error:";
   //     qDebug() << "\tThe type of your IObject is" << document->getType();
        qDebug() << "\tThe controller ImageController handle " << this->getSupportedType() << " type.";
    }

    label = new QLabel("Loading image...");
    //if (data->isDownloaded())
       dl();
    qDebug() << "label geneted";
    return (label);
}

void        ImageController::dl()
{
    QString fileName;
    fileName = data->file()->fileName();
//fileName  = "/tmp/15";
    QImage  *image = new QImage(fileName);
    if (image->isNull())
    {
        qDebug() << "An error occured during image generation";
        return ;
    }
    QPixmap pix = QPixmap::fromImage(*image);
    label->setPixmap(pix);
    delete image;
}

void    ImageController::reload()
{
    QString fileName;
    fileName = data->file()->fileName();

    qDebug() << "Image name: " << fileName;
    QImage  *image = new QImage(fileName);
    if (image->isNull())
    {
        qDebug() << "An error occured during image generation";
        return ;
    }
    QPixmap pix = QPixmap::fromImage(*image);
    label->setPixmap(pix);
    //delete image;
}

QWidget        *ImageController::editDocument(QFile *file, ILessonDocument *doc)
{
    return 0;
}

