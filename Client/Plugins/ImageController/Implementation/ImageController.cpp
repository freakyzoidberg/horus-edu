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

QWidget*            ImageController::createDocumentWidget(IItems *parent, ILessonDocument *document)
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

    label = new QLabel("Loading image...", parent);
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

void    ImageController::clean(IItems *widget)
{

}

void    ImageController::resizeWidget(IItems *widget)
{

}

 QWidget        *ImageController::editDocument(QFile *file, IItems *parent, ILessonDocument *doc)
{
    QString     fileName = file->fileName();
    QLabel      *editLabel = new QLabel("Loading image...", parent);
    QImage      *image = new QImage(fileName);
    QPushButton *save = new QPushButton(tr("Save changes"));

    if (image->isNull())
    {
        editLabel->setText(tr("An error occurs. Cannot open image."));
        return parent;
    }

    QPixmap pix = QPixmap::fromImage(*image);
    label->setPixmap(pix);
    delete image;
    this->parent = parent;
    doc->setTitle(fileName);
    doc->setObjectName(QString(doc->getId()));
    connect(save, SIGNAL(clicked()), this, SLOT(saveModifs()));
    return parent;
}

 void       ImageController::saveChanges()
 {
    parent->close();
 }
