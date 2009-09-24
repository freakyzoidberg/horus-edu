#ifndef __TEXTCONTROLLER_H__
# define __TEXTCONTROLLER_H__

# include <QtPlugin>

# include "../../../../Common/Plugin.h"
# include "../../LessonManager/IDocumentController.h"
# include "../../Course/IItems.h"

class TextController : public Plugin, public IDocumentController
{
    Q_OBJECT
    Q_INTERFACES(Plugin)
    Q_INTERFACES(IDocumentController)

public:
	const QString		pluginName() const;
	const QString		pluginVersion() const;
        const QString		getSupportedType() const;
        QWidget                 *createDocumentWidget(IItems *parent, ILessonDocument *document);
        void                    editWidget(ILessonDocument *document, IItems *parent);
        void                    resizeWidget(IItems *);
        void                    clean(IItems *);
        ILessonDocument *addDocument(QFile *metadata, QWidget *parent);
        void      editDocument(QFile *metadata, QWidget *parent, ILessonDocument *);
};

#endif // __TEXTCONTROLLER_H__
