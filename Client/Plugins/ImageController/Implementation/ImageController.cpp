#include "ImageController.h"

#include <QLabel>
#include <QImage>
#include <QPixmap>

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

QWidget*            ImageController::createDocumentWidget(QWidget *parent, ILessonDocument *document)
{
    int fileId;

    fileId = document->getParameters().value("fileId").toInt();
    data = pluginManager->findPlugin<FileDataPlugin*>()->getFile(fileId);
    this->connect(data, SIGNAL(downloaded()), this, SLOT(dl()));

    if (document->getType() != this->getSupportedType())
    {
        qDebug() << "[Plugin ImageController] Type error:";
        qDebug() << "\tThe type of your IObject is" << document->getType();
        qDebug() << "\tThe controller ImageController handle " << this->getSupportedType() << " type.";
    }

    label = new QLabel("Loading image...", parent);
    dl();
    return (label);
}

void        ImageController::dl()
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
    delete image;
}
