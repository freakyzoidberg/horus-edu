#include "TextController.h"

#include <QLabel>

const QString    TextController::pluginName() const
{
    return ("textController");
}

const QString    TextController::pluginVersion() const
{
    return ("0.2");
}

const QString      TextController::getSupportedType() const
{
    return ("text");
}

QWidget*			TextController::createDocumentWidget(QWidget *parent, ILessonDocument *document)
{
    QLabel *label = 0;

	if (document->getParameters()["input"] == "content")
    {
        label = new QLabel(parent);
        label->setText(document->getContent());
    }
	return (label);
}