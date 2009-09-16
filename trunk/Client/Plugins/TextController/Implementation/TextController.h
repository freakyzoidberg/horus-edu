#ifndef __TEXTCONTROLLER_H__
# define __TEXTCONTROLLER_H__

# include <QtPlugin>

# include "../../../../Common/Plugin.h"
# include "../../LessonManager/IDocumentController.h"

class TextController : public Plugin, public IDocumentController
{
    Q_OBJECT
    Q_INTERFACES(Plugin)
    Q_INTERFACES(IDocumentController)

public:
	const QString		pluginName() const;
	const QString		pluginVersion() const;
    const QString		getSupportedType() const;
	QWidget*			createDocumentWidget(QWidget *parent, ILessonDocument *document);
};

#endif // __TEXTCONTROLLER_H__
