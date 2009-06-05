#ifndef PDF_CONTROLLER_H
#define PDF_CONTROLLER_H

#include <QObject>

#include "../../LessonManager/ILessonManager.h"
#include <IClientPlugin.h>
#include <IPdfController.h>

class   pdfController : public IClientPlugin, public IPdfController,
                        public ILesson::IPage::IObject::IController
{
        Q_OBJECT
        Q_INTERFACES(IClientPlugin)

    public:
        pdfController();
        ~pdfController();

        //! Return the name of the plugin.
        /*!
          \return the variable name
        */
        const QByteArray        getName() const;

        //! Return the version of the plugin
        /*!
          \return the variable version
        */
        const QByteArray        getVersion() const;

        //! Return the conflicst between plugins
        /*!
          \return the variable pluginsConflicts
        */
        QStringList     getPluginsConflicts() const;

        //! Return the list of plugins requiered
        /*!
          \return the variable pluginsRequiered
        */
        QStringList     getPluginsRequired() const;

        //! Return the list of plugins recommended
        /*!
            \return the variable pluginsRecommended
        */
        QStringList     getPluginsRecommended() const;

        //QStringList           getExports();

        //! Overload of the event() method
        /*!
          \param event the event received by the plugin
          \return true if the event was successfully handled, false eitherway
        */
        bool    event(QEvent *event);

         //! Handle the event loadEvent
        /*!
          \param event the event received by the plugin
          \return true if the event was successfully handled, false eitherway
        */
        bool    eventHandlerLoad(QEvent *event);

        //! Handle the event unloadEvent
        /*!
          \param event the event received by the plugin
          \return true if the event was successfully handled, false eitherway
        */
        bool    eventHandlerUnload(QEvent *event);

         //! Indicates which type is supported by the plugin.
                /*!
                    \return A string matching a specific type of page object.
                */
        const QString&  getSupportedType() const;

         //! Allows the PageDisplayer plugin to give an ILesson::IPage::IObject pointer to the dedicated plugin.
         /*!
          The dedicated plugin needs one or several ILesson::IPage::IObject(s) to display. It should keep
          track of the different objects it is asked to display.
          This method should only be used by the PageDisplayer (or similar) plugin.
          When the PageDisplayer plugin wants to stop displaying one of the ILesson::IPage::IObject(s)
          it will call the method hideObject().
          \param object A pointer to the ILesson::IPage::IObject to show.
         */
         void    showObject(ILesson::IPage::IObject *object);

                //! Allows the PageDisplayer plugin to require an ILesson::IPage::IObject to be activated by the dedicated plugin.
                /*!
                    The notion of "activation" of an ILesson::IPage::IObject makes sense if an ILesson::IPage::IObject is a multimedia object
                    such as a Video or an interactive quizz (etc), before activation the ILesson::IPage::IObject should behave
                    as a static image. Once the activation order is sent, the ILesson::IPage::IObject should be brought to life
                    by the dedicated plugin.
                    \param object A pointer to the ILesson::IPage::IObject to activate.

                */
         void    activateObject(ILesson::IPage::IObject *object);

                //! Requires the dedicated plugin to hide an ILesson::IPage::IObject that has been previously displayed.
                /*!
                    This method is typically called by the PageDisplayer plugin before switching to another page.
                    \param object A pointer to the ILesson::IPage::IObject to hide.
                */
         void    hideObject(ILesson::IPage::IObject *object);

                //! Requires the dedicated plugin to configure the content of an ILesson::IPage::IObject.
                /*!
                    This method is typically called by the editor, when the teacher creates a new ILesson::IPage::IObject
                    of a specific type, he wants his object to actually contain 'something'. However as
                    each object type is different, the higher level plugin doesn't know which files, to
                    open, and which parameters to set to get the ILesson::IPage::IObject to actually display 'something'.
                    This is the role of the dedicated plugin to allow the teacher to configure his newly (or not)
                    created object.
                    \param object A pointer to the ILesson::IPage::IObject to configure.
                */
          void    configureObject(ILesson::IPage::IObject *object);

        void    setObject(ILesson::IPage::IObject *object);
        const QList<ILesson::IPage::IObject * > & getObjects();

      private:
        //! the name of the plugin
        QByteArray  name;

        //!the version of the plugin
        QByteArray  version;

        //! The list of the name of the plugins conflicting with the dispPDF plugin
        QStringList pluginsConflicts;

        //! The list of the name of plugins requiered by the dispPDF plugin
        QStringList plugindRequired;

        //! The list of the name of plugins recommended by the dispPDF plugin
        QStringList pluginsRecommended;

        QString     supportedType;
        QList<ILesson::IPage::IObject *> objects;
 };

#endif /* PDF_CONTROLLER_H */
