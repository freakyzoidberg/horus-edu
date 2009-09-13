#ifndef ICONTROLLER_H
#define ICONTROLLER_H

#include <QObject>

#include "Lesson.h"

//! Interface of an object controller.
/*!
    An object controller is a class that allows to display the content of
    an object and bring it to life. The implementations of IController are
    defined in separate plugins. The implementation of IObject is provided by
    the LessonManager plugin, users should not provide their own implementation.
    However, no implementation of IController is provided by LessonManager.
    This is the role of some dedicated plugins. The overload of the method
    getSupportedType indicates which plugin supports which type.
*/
class IController
{
public:
    virtual ~IController() {}

    //! Indicates which type is supported by the plugin.
    /*!
        \return A string matching a specific type of page object.
    */
    virtual const QString  getSupportedType() const = 0;

    //! Allows the PageDisplayer plugin to give an IObject pointer to the dedicated plugin.
    /*!
        The dedicated plugin needs one or several IObject(s) to display. It should keep
        track of the different objects it is asked to display.
        This method should only be used by the PageDisplayer (or similar) plugin.
        When the PageDisplayer plugin wants to stop displaying one of the IObject(s)
        it will call the method hideObject().
        \param object A pointer to the IObject to show.
    */
    virtual void    showObject(LObject *object) = 0;

    //! Allows the PageDisplayer plugin to require an IObject to be activated by the dedicated plugin.
    /*!
        The notion of "activation" of an IObject makes sense if an IObject is a multimedia object
        such as a Video or an interactive quizz (etc), before activation the IObject should behave
        as a static image. Once the activation order is sent, the IObject should be brought to life
        by the dedicated plugin.
        \param object A pointer to the IObject to activate.

    */
    virtual void    activateObject(LObject *object) = 0;

    //! Requires the dedicated plugin to hide an IObject that has been previously displayed.
    /*!
        This method is typically called by the PageDisplayer plugin before switching to another page.
        \param object A pointer to the IObject to hide.
    */
    virtual void    hideObject(LObject *object) = 0;

    //! Requires the dedicated plugin to configure the content of an IObject.
    /*!
        This method is typically called by the editor, when the teacher creates a new IObject
        of a specific type, he wants his object to actually contain 'something'. However as
        each object type is different, the higher level plugin doesn't know which files, to
        open, and which parameters to set to get the IObject to actually display 'something'.
        This is the role of the dedicated plugin to allow the teacher to configure his newly (or not)
        created object.
        \param object A pointer to the IObject to configure.
    */
    virtual void    configureObject(LObject *object) = 0;
};

Q_DECLARE_INTERFACE(IController, "net.horus.Client.Plugin.LessonManager.ControllerInterface/1.0");

#endif // ICONTROLLER_H
