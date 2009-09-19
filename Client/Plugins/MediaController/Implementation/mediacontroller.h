#ifndef MEDIACONTROLLER_H
#define MEDIACONTROLLER_H

#include <phonon/videowidget.h>
#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>

# include "../../../../Common/Plugin.h"
# include "../../../../Common/FileData.h"
# include "../../../../Common/FileDataPlugin.h"
# include "../../LessonManager/ILessonManager.h"
# include "../../LessonManager/IDocumentController.h"
# include "../../PdfDisplayer/IPdfRendering.h"

class MediaController : public Plugin, public IDocumentController
{
   Q_OBJECT
   Q_INTERFACES(Plugin)
   Q_INTERFACES(IDocumentController)

   public:
        MediaController();
        ~MediaController();
    //! Return the version of the plugin
        /*!
          \return the variable version
        */
        const QString   pluginVersion() const;

         //! Indicates which type is supported by the plugin.
         /*!
            \return A string matching a specific type of page object.
         */
        const QString   getSupportedType() const;
        const QString   pluginName() const;
        QWidget*        createDocumentWidget(QWidget *parent, ILessonDocument *document);

     private slots:
        void    dl();
        void    reload();

     private:
        FileData                *data;
        QString                 supportedType;
        Phonon::VideoWidget     *vid;
        Phonon::MediaObject     *media;
        QWidget                 *parent;
};

#endif // MEDIACONTROLLER_H
