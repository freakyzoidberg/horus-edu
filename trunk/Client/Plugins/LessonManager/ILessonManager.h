#ifndef ILESSONMANAGER_H
#define ILESSONMANAGER_H

#include "ILesson.h"

//! Interface of the plugin ILessonManager
/*!
    This interface describes the methods used in the plugin to load a representation
    of a lesson as well as save a lesson or create a new lesson.
*/
class ILessonManager
{
    public:
    //! Retrieves a specific lesson.
    /*!
        \param fileId The metadata file representing the lesson.
        \return The representation of the lesson.
    */
    virtual ILesson*    getLesson(quint32 fileId) = 0;

    //! Saves a lesson into a metadata file.
    /*!
        \param fileId The name of the metadata file in which to save the lesson.
        \param lesson The lesson representation to save.
    */
    virtual void        saveLesson(quint32 fileId, ILesson *lesson) = 0;

    //! Creates a new lesson.
    /*!
        \param fileId The metadata file representing the lesson to create.
        \return The representation of the lesson newly created.
    */
    virtual ILesson*    createNewLesson(quint32 fileId) = 0;

    //! Displays a page of a lesson in the specified widget.
    /*!
        \param page The page to display.
        \param widget The widget in which the page will be displayed.
    */
    virtual void        displayPage(ILesson::IPage *page, QWidget *widget) = 0;

    //! Removes the displayed page from the display widget.
    /*!
        This method should be called subsequently to a call to displayPage().
    */
    virtual void        hideCurrentPage() = 0;
};

Q_DECLARE_INTERFACE(ILessonManager, "net.horus.Client.LessonManagerInterface/1.0");

#endif // ILESSONMANAGER_H
