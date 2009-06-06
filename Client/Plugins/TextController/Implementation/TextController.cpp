#include "TextController.h"

#include <QDebug>

#include "../../ClientEvents.h"

Q_EXPORT_PLUGIN2(TextController, TextController)

extern QEvent::Type ClientEvents::LoadPluginEvent;

TextController::TextController()
{
    qDebug() << "coucou";
}

const QByteArray    TextController::getName() const
{
    return ("textController");
}

const QByteArray    TextController::getVersion() const
{
    return ("0.1");
}

QStringList         TextController::getPluginsRequired() const
{
    return (QStringList());
}

QStringList         TextController::getPluginsConflicts() const
{
    return (QStringList());
}

QStringList         TextController::getPluginsRecommended() const
{
    return (QStringList());
}

bool                TextController::event(QEvent *event)
{
    if (event->type() == ClientEvents::LoadPluginEvent)
        return (true);
    qDebug() << "TextController: Received Event not managed" << event;
    return (false);
}

const QString&      TextController::getSupportedType() const
{
    return (QString("text"));
}

void                TextController::showObject(ILesson::IPage::IObject *object)
{
}

void                TextController::activateObject(ILesson::IPage::IObject *object)
{
}

void                TextController::hideObject(ILesson::IPage::IObject *object)
{
}

void                TextController::configureObject(ILesson::IPage::IObject *object)
{
}
