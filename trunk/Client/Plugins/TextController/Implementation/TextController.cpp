#include "TextController.h"

#include <QTextEdit>
#include <QTextEdit>
#include <QPushButton>

const QString       TextController::pluginName() const
{
    return ("textController");
}

const QString       TextController::pluginVersion() const
{
    return ("0.2");
}

const QString       TextController::getSupportedType() const
{
    return ("text");
}

QWidget*            TextController::createDocumentWidget(IItems *parent, ILessonDocument *document)
{
	QTextEdit *textedit = 0;

    if (document->getParameters()["input"] == "content")
    {
		textedit = new QTextEdit(parent);
		textedit->setReadOnly(true);
		textedit->setText(document->getContent());
    }
	return (textedit);
}

void                TextController::clean(IItems *widget)
{

}

void                TextController::resizeWidget(IItems *widget)
{

}

QWidget             *TextController::editDocument(QFile *metadata, IItems *parent,
                                                  ILessonDocument *document)
{
    QTextEdit           *textEditor = new QTextEdit(parent);
    QPushButton         *save = new QPushButton("Save", parent);
    QTextDocument       *text = new QTextDocument(document->getContent());

    textEditor->setDocument(text);
    document->setContent(textEditor->document()->toPlainText());
    connect(save, SIGNAL(clicked()), this, SLOT(saveModifs()));
    this->parent = parent;
    return parent;
}

void                TextController::saveModifs()
{

    this->parent->close();
}
