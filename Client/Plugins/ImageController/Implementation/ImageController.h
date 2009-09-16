#ifndef __IMAGECONTROLLER_H__
# define __IMAGECONTROLLER_H__

# include <QtPlugin>

# include <QLabel>
# include <QImage>

# include "../../../../Common/Plugin.h"
# include "../../LessonManager/IDocumentController.h"
# include "../../LessonManager/ILessonManager.h"
# include "../../LessonManager/IDocumentController.h"

class ImageController : public Plugin, public IDocumentController
{
    Q_OBJECT
    Q_INTERFACES(Plugin)
    Q_INTERFACES(IDocumentController)

public:
	const QString		pluginName() const;
	const QString		pluginVersion() const;
        const QString		getSupportedType() const;
        QWidget*		createDocumentWidget(QWidget *parent, ILessonDocument *document);

 private slots:
        void    dl();

  private:
        QLabel      *label;
        FileData    *data;
        QString     supportedType;
};

#endif // __IMAGECONTROLLER_H__
