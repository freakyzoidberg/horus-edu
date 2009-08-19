#ifndef __TEXTCONTROLLER_H__
# define __TEXTCONTROLLER_H__

# include <QtPlugin>

# include "../../../../Common/Plugin.h"
# include "../../LessonManager/ILesson.h"
# include "../../LessonManager/IController.h"

class TextController : public Plugin, public IController
{
    Q_OBJECT
    Q_INTERFACES(Plugin)
    Q_INTERFACES(IController)

public:
	const QString		pluginName() const;
	const QString		pluginVersion() const;
    const               QString  getSupportedType() const;
    void                showObject(ILesson::IPage::IObject *object);
    void                activateObject(ILesson::IPage::IObject *object);
    void                hideObject(ILesson::IPage::IObject *object);
    void                configureObject(ILesson::IPage::IObject *object);
};

#endif // __TEXTCONTROLLER_H__
