#ifndef __PDFCONTROLLER_H__
# define __PDFCONTROLLER_H__

# include <QObject>
# include <QLabel>

# include "../../../../Common/Plugin.h"
# include "../../LessonManager/ILessonManager.h"
# include "../../LessonManager/IDocumentController.h"

class   PdfController : public Plugin, public IDocumentController
{
        Q_OBJECT
        Q_INTERFACES(Plugin)
        Q_INTERFACES(IDocumentController)

    public:
        PdfController();
        ~PdfController();

        //! Return the name of the plugin.
        /*!
          \return the variable name
        */
        const QString        pluginName() const;

        //! Return the version of the plugin
        /*!
          \return the variable version
        */
        const QString        pluginVersion() const;

         //! Indicates which type is supported by the plugin.
                /*!
                    \return A string matching a specific type of page object.
                */
        const QString  getSupportedType() const;

        QWidget* createDocumentWidget(QWidget *parent, ILessonDocument *document);

      private:
        QLabel  *label;

        QString     supportedType;
};

#endif /* __PDF_CONTROLLER_H__ */
