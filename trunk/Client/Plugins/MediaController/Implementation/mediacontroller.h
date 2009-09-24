#ifndef MEDIACONTROLLER_H
#define MEDIACONTROLLER_H

#include <phonon/videowidget.h>
#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <phonon/videoplayer.h>

# include "../../../../Common/Plugin.h"
# include "../../../../Common/FileData.h"
# include "../../../../Common/FileDataPlugin.h"
# include "../../LessonManager/ILessonManager.h"
# include "../../LessonManager/IDocumentController.h"
# include "../../PdfDisplayer/IPdfRendering.h"
# include "../../Course/IItems.h"
# include "player.h"

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
        const QString           pluginVersion() const;

        //! Indicates which type is supported by the plugin.
        /*!
           \return A string matching a specific type of page object.
        */
        const QString           getSupportedType() const;
        const QString           pluginName() const;
        QWidget*                createDocumentWidget(IItems *parent, ILessonDocument *document);
        void                    editWidget(ILessonDocument *document, IItems *parent);
        void                    resizeWidget(IItems *);
        void                    clean(IItems *);

     private slots:
        void                    dl();
        void                    reload();

     private:
        FileData                *data;
        QString                 supportedType;
        Phonon::VideoWidget     *vid;
        Phonon::VideoPlayer     *vidPlayer;
        Phonon::MediaObject     *media;
        IItems                  *parent;
};

#endif // MEDIACONTROLLER_H
