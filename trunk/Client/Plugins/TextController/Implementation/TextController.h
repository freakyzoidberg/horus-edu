#ifndef TEXTCONTROLLER_H
#define TEXTCONTROLLER_H

#include "TextController_global.h"

#include <QtPlugin>
#include <QWidget>

#include "../../IClientPlugin.h"
#include "../LessonManager/ILesson.h"
#include "../LessonManager/IController.h"

class TEXTCONTROLLERSHARED_EXPORT TextController : public IClientPlugin, public IController
{
    Q_OBJECT
    Q_INTERFACES(IClientPlugin)
    Q_INTERFACES(IController)

public:
    TextController();
    const QByteArray    getName() const;
    const QByteArray    getVersion() const;
    QStringList         getPluginsConflicts() const;
    QStringList         getPluginsRequired() const;
    QStringList         getPluginsRecommended() const;
    bool                event(QEvent *event);
    const               QString&  getSupportedType() const;
    void                showObject(ILesson::IPage::IObject *object);
    void                activateObject(ILesson::IPage::IObject *object);
    void                hideObject(ILesson::IPage::IObject *object);
    void                configureObject(ILesson::IPage::IObject *object);

private:
    QString             type;
    QWidget              *text;
};

#endif // TEXTCONTROLLER_H
