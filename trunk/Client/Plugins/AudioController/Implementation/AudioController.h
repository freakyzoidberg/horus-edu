#ifndef MEDIACONTROLLER_H
#define MEDIACONTROLLER_H

#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>

# include "../../../../Common/Plugin.h"
# include "../../../../Common/FileData.h"
# include "../../../../Common/FileDataPlugin.h"
# include "../../LessonManager/ILessonManager.h"
# include "../../LessonManager/IDocumentController.h"
# include "../../PdfDisplayer/IPdfRendering.h"
# include "audioplayer.h"

class AudioController : public Plugin, public IDocumentController
{
   Q_OBJECT
   Q_INTERFACES(Plugin)
   Q_INTERFACES(IDocumentController)

   public:
        AudioController();
        ~AudioController();
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
        QWidget*        createDocumentWidget(ILessonDocument *document);
        QWidget         *editDocument(QFile *metadata, ILessonDocument *);

     private slots:
        void            dl();
        void            reload();

     private:
        FileData                *data;
        QString                 supportedType;
        Phonon::MediaObject     *media;
};

#endif // MEDIACONTROLLER_H
