#ifndef ILESSON_H
#define ILESSON_H

#include <QString>
#include <QList>
#include <QPointF>
#include <QSizeF>
#include <QtGui/QWidget>
#include <QAbstractItemModel>

class IController;

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

            //! Retrieves a list of file ids.
            /*!
                The qint32s refer to an ID of the actual file source in the server database.
            */
            virtual const QList<quint32>&    getRequiredFiles() const = 0;

            //! Adds a file dependency for the specified plugin.
            /*!
                \param id The file id.
            */
            virtual void                addRequiredFile(quint32 id) = 0;

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

            virtual const QString&      getContent() const = 0;

            virtual void                setContent(const QString& content) = 0;

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

Q_DECLARE_METATYPE(ILesson::IPage *);

#endif // ILESSON_H