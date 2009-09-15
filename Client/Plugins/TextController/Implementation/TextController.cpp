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

void                TextController::showObject(LObject *object)
{
    QTextBrowser *browser;

//    if (object->getParameters() == "text")
//    {
//        browser = new QTextBrowser(object->getWidget());
//        browser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
//        browser->insertPlainText(object->getContent());
//    }
    //else if (object->getParameters() == "file")
	// DO SOMETHING !!
}

void                TextController::activateObject(LObject *object)
{
	// DO SOMETHING !!
}

void                TextController::hideObject(LObject *object)
{
	// DO SOMETHING !!
}

void                TextController::configureObject(LObject *object)
{
	// DO SOMETHING !!
}
