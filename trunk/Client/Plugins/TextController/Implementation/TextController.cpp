#include "TextController.h"

#include <QTextBrowser>

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
    QTextBrowser *browser = 0;

	if (document->getParameters()["input"] == "content")
    {
        browser = new QTextBrowser(parent);
        browser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        browser->insertPlainText(document->getContent());
    }
	return (browser);
}