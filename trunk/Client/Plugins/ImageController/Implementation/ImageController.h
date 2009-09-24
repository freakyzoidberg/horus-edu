#ifndef __IMAGECONTROLLER_H__
# define __IMAGECONTROLLER_H__

# include <QtPlugin>

# include <QLabel>
# include <QImage>

# include "../../../../Common/Plugin.h"
# include "../../LessonManager/IDocumentController.h"
# include "../../LessonManager/ILessonManager.h"
# include "../../LessonManager/IDocumentController.h"
# include "../../Course/IItems.h"

class ImageController : public Plugin, public IDocumentController
{
    Q_OBJECT
    Q_INTERFACES(Plugin)
    Q_INTERFACES(IDocumentController)

public:
	const QString		pluginName() const;
	const QString		pluginVersion() const;
        const QString		getSupportedType() const;
        QWidget*		createDocumentWidget(IItems *parent, ILessonDocument *document);
        void                    editWidget(ILessonDocument *document, IItems *parent);
        void                    resizeWidget(IItems *);
        void                    clean(IItems *);

 private slots:
        void    dl();
        void    reload();

  private:
        QLabel      *label;
        FileData    *data;
        QString     supportedType;
};

#endif // __IMAGECONTROLLER_H__
