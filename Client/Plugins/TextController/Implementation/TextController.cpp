#include "TextController.h"

#include <QLabel>
#include <QTextEdit>
#include <QPushButton>

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

QWidget*			TextController::createDocumentWidget(IItems *parent, ILessonDocument *document)
{
    QLabel *label = 0;

	if (document->getParameters()["input"] == "content")
    {
        label = new QLabel(parent);
        label->setText(document->getContent());
    }
	return (label);
}

void    TextController::clean(IItems *widget)
{

}

void    TextController::resizeWidget(IItems *widget)
{

}

QWidget      *TextController::editDocument(QFile *metadata, QWidget *parent, ILessonDocument *document)
{
    QTextEdit           *textEditor = new QTextEdit(parent);
    QPushButton         *save = new QPushButton("Save", parent);
    return 0;
}
