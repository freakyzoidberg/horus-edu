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

void                TextController::showObject(ILesson::IPage::IObject *object)
{
    QTextBrowser *browser;

    if (object->getParameters() == "text")
    {
        browser = new QTextBrowser(object->getWidget());
        browser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        browser->insertPlainText(object->getContent());
    }
    //else if (object->getParameters() == "file")
	// DO SOMETHING !!
}

void                TextController::activateObject(ILesson::IPage::IObject *object)
{
	// DO SOMETHING !!
}

void                TextController::hideObject(ILesson::IPage::IObject *object)
{
	// DO SOMETHING !!
}

void                TextController::configureObject(ILesson::IPage::IObject *object)
{
	// DO SOMETHING !!
}
