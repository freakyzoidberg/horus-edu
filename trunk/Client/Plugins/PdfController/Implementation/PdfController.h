#ifndef __PDFCONTROLLER_H__
# define __PDFCONTROLLER_H__

# include <QObject>
# include <QLabel>
# include <QRectF>

# include "../../../../Common/Plugin.h"
# include "../../../../Common/FileData.h"
# include "../../../../Common/FileDataPlugin.h"
# include "../../LessonManager/ILessonManager.h"
# include "../../LessonManager/IDocumentController.h"
# include "../../PdfDisplayer/IPdfRendering.h"
# include "../../Course/IItems.h"

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
        const QString   getSupportedType() const;

        QWidget*        createDocumentWidget(IItems *parent, ILessonDocument *document);
        void            resizeWidget(IItems *);
        void            clean(IItems *);
        QWidget         *editDocument(QFile *metadata, QWidget *parent, ILessonDocument *);

     private slots:
        void            dl();
        void            reload();

     private:
        QLabel          *label;
        FileData        *data;
        QString         supportedType;
        IPdfRendering   *pdf;
        QRectF          *rect;
        int             page;
};

#endif /* __PDF_CONTROLLER_H__ */
