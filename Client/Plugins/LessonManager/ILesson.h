#ifndef ILESSON_H
#define ILESSON_H

#include <QString>
#include <QList>
#include <QPointF>
#include <QSizeF>
#include <QtGui/QWidget>
#include <QAbstractItemModel>

//! Interface of a lesson metadata representation.
/*!
    This interface describes a lesson and its different components,
    such as the different sections, subsections and pages as well as
    the content of the pages. To obtain a concrete lesson object or to create
    a new concrete lesson, use the LessonManager plugin main class (more specifically
    the part which implements the ILessonManager interface).
    Don't create your own concrete class for the types ILesson and its subtypes,
    use the types provided by the plugin.
*/
class ILesson : public QAbstractItemModel
{
public:
    virtual ~ILesson() {}

    //! Interface of a lesson element
    /*!
        A lesson element is either a page (IPage) or a section (ISection).
    */
    class IElement
    {
        public:
        virtual ~IElement() {}

        //! Type of an element
        enum Type
        {
            SECTION, /*!< The concrete class is of type ISection */
            PAGE /*!< The concrete class is of type IPage */
        };

        //! Retrieves the element type. The element is either a section or a page.
        /*!
            \return The type of the element.
        */
        virtual const Type          getType() const = 0;

        //! Retrieves the title of the element.
        /*!
            \return The title of the element.
        */
        virtual const QString&          getTitle() const = 0;

        //! Sets the title of the element.
        /*!
            \param title The title of the element.
        */
        virtual void                    setTitle(const QString& title) = 0;
    };

    //! Interface of a lesson section.
    /*!
        A section of a lesson is a container for subsections or pages.
        It is meant for the teacher to organize his lesson as a hierarchy.
    */
    class ISection : virtual public IElement
    {
        public:
        virtual ~ISection() {}

        //! Retrieves the elements contained in the section, elements can be either sections or pages.
        /*!
            \return A list of elements in the section. To add a page or section, use the appropriate methods
            of ILesson.
        */
        virtual const QList<IElement *>&  getElements() const = 0;
    };

    //! Interface of a lesson page.
    /*!
        A page is a fixed size screen meant to be displayed on the teacher and
        the students computers. It is the element of a lesson that contains the
        actual displayable content such as text, PDF elements, images, quizz, etc...
    */
    class IPage : virtual public IElement
    {
        public:
        virtual ~IPage() {}

        //! Interface of a page object.
        /*!
            A page object is a displayable zone which contains static or
            interactive page content, the content types (for example: text, PDF, image, ...)
            are controlled by an implementation of the class IController. These controllers
            can be found in appropriate plugins.
        */
        class IObject
        {
            public:
            virtual ~IObject() {}

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
                virtual const QString&  getSupportedType() const = 0;

                //! Allows the PageDisplayer plugin to give an IObject pointer to the dedicated plugin.
                /*!
                    The dedicated plugin needs one or several IObject(s) to display. It should keep
                    track of the different objects it is asked to display.
                    This method should only be used by the PageDisplayer (or similar) plugin.
                    When the PageDisplayer plugin wants to stop displaying one of the IObject(s)
                    it will call the method hideObject().
                    \param object A pointer to the IObject to show.
                */
                virtual void    showObject(IObject *object) = 0;

                //! Allows the PageDisplayer plugin to require an IObject to be activated by the dedicated plugin.
                /*!
                    The notion of "activation" of an IObject makes sense if an IObject is a multimedia object
                    such as a Video or an interactive quizz (etc), before activation the IObject should behave
                    as a static image. Once the activation order is sent, the IObject should be brought to life
                    by the dedicated plugin.
                    \param object A pointer to the IObject to activate.

                */
                virtual void    activateObject(IObject *object) = 0;

                //! Requires the dedicated plugin to hide an IObject that has been previously displayed.
                /*!
                    This method is typically called by the PageDisplayer plugin before switching to another page.
                    \param object A pointer to the IObject to hide.
                */
                virtual void    hideObject(IObject *object) = 0;

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
                virtual void    configureObject(IObject *object) = 0;
            };

            //! Retrieves the position of the object.
            /*!
                \return The position of the object in percent of the workspace size.
            */
            virtual const QPointF&      getPosition() const = 0;

            //! Sets the object's position.
            /*!
                \param pos The position of the object in percent of the workspace size.
            */
            virtual void                setPosition(const QPointF& pos) = 0;

            //! Retrieves the size of the object.
            /*!
                \return The size of the object in percent of the workspace size.
            */
            virtual const QSizeF&       getSize() const = 0;

            //! Sets the object's size.
            /*!
                \param size The size of the object in percent of the workspace size.
            */
            virtual void                setSize(const QSizeF& size) = 0;

            //! Retrieves the type of the object.
            /*!
                \return A string describing the type of the object, the appropriate
                plugins need to be loaded according to the type, they provide an implementation
                of IController.
            */
            virtual const QString&      getType() const = 0;

            //! Retrieves the container for the object to display.
            /*!
                The container is a QWidget which allows the implementors of IController
                to display content. The position and size of this QWidget should not be modified by
                the implementors of IController, they are decided in higher level plugins such as the
                editor or lesson displayer and the controllers should comply with them.
            */
            virtual QWidget*            getWidget() = 0;

            //! Sets the container for the object to display.
            /*!
                This method should not be called by the IController implementations.
                It is the task of the higher level plugins to create the widget in which to
                display the object.
                \param widget The Qwidget to set.
            */
            virtual void                setWidget(QWidget *widget) = 0;

            //! Retrieves a map of filenames associated with their database ID required by the object.
            /*!
                The string refers to a local filename which will be used by the IObject controller to
                display the object.
                The int refers to an ID of the actual file source in the server database.
            */
            virtual const QMap<QString, int>&    getRequiredFiles() const = 0;

            //! Adds a file dependency for the specified plugin.
            /*!
                \param fileName The local file name.
            */
            virtual void                addRequiredFile(QString fileName) = 0;

            //! Retrieves the object parameters.
            /*!
                \return The object parameters.
                The control of the format and content of the string
                is up to the specific controller of an object type.
            */
            virtual const QString&      getParameters() const = 0;

            //! Sets the object parameters.
            /*!
                \param params A string describing the parameters of the object.
                The control of the format and content of the string
                is up to the specific controller of an object type.
            */
            virtual void                setParameters(const QString& params) = 0;

            //! Retrieves the controller of an object.
            /*!
                \return A pointer to the appropriate controller or NULL if the controller was not found.
            */
            virtual IController*        getController() = 0;

            //! Sets the controller of an object.
            /*!
                \param ctrl A pointer to the appropriate controller for the object.
            */
            virtual void                setController(IController *ctrl) = 0;
        };

        //! Retrieves the objects contained in the page.
        /*!
            \return A list of objects in the page. To add an object use the addObject method.
        */
        virtual const QList<IObject *>&   getObjects() const = 0;

        //! Adds an object in the page.
        /*!
            \param object The object to add.
        */
        virtual void                    addObject(IObject* object) = 0;
    };

public:
    //! Retrieves the title of the lesson.
    /*!
        \return The title of the lesson.
    */
    virtual const QString&          getTitle() const = 0;

    //! Sets the title of the lesson.
    /*!
        \param title The title of the lesson.
    */
    virtual void                    setTitle(const QString& title) = 0;

    //! Retrieves the elements contained in the lesson, elements can be either sections or pages.
    /*!
        \return A list of elements in the lesson. To add a page or section, use the appropriate methods.
    */
    virtual const QList<IElement *>&  getElements() const = 0;

    //! Adds an element to the lesson.
    /*!
        \param type Type of the element to add, either PAGE or SECTION.
        \param title Title of the element.
    */
    virtual IElement*               addElement(IElement::Type type, const QString& title) = 0;

    //! Adds an element to the lesson in the specified section or subsection.
    /*!
        \param type Type of the element to add, either PAGE or SECTION.
        \param title Title of the element.
        \param section Section or subsection in which the element should be inserted.
    */
    virtual IElement*               addElement(IElement::Type type, const QString& title, const ISection* section) = 0;
};

#endif // ILESSON_H
