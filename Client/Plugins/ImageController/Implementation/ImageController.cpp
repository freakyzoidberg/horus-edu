#include "ImageController.h"

#include <QLabel>

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

QWidget*			ImageController::createDocumentWidget(QWidget *parent, ILessonDocument *document)
{

	int fileId;
	QLabel *label = 0;

    fileId = document->getParameters().value("fileId").toInt();
    data = pluginManager->findPlugin<FileDataPlugin*>()->getFile(fileId);
    this->connect(data, SIGNAL(downloaded()), this, SLOT(dl()));
    label = new QLabel("Loading image...", parent);
	return (label);
}