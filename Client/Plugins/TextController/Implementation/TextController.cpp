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

QWidget*            TextController::createDocumentWidget(ILessonDocument *document)
{
	QTextEdit *textedit = 0;

    if (document->getParameters()["input"] == "content")
    {
                textedit = new QTextEdit;
		textedit->setReadOnly(true);
		textedit->setText(document->getContent());
    }
	return (textedit);
}

QWidget             *TextController::editDocument(QFile *metadata, ILessonDocument *document)
{
    QTextEdit           *textEditor = new QTextEdit;
    QPushButton         *save = new QPushButton("Save");
    QTextDocument       *text = new QTextDocument(document->getContent());

    textEditor->setDocument(text);
    document->setContent(textEditor->document()->toPlainText());
    //connect(save, SIGNAL(clicked()), this, SLOT(saveModifs()));
    return textEditor;
}

