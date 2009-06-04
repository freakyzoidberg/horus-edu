#ifndef LESSON_H
#define LESSON_H

#include <QMap>
#include <QString>
#include "../ILesson.h"

//! Convenience class to allow polymorphic cast on LSection, LPage and Lesson
class LItem
{
 public:
    LItem() {}
    virtual ~LItem() {}
};

//! Provides an implementation of ILesson::ISection to be used by the plugin.
class LSection : public ILesson::ISection, public LItem
{
public:
    LSection();
    ~LSection() {}

    const Type                      getType() const;
    const QString&                  getTitle() const;
    void                            setTitle(const QString& title);

    QList<ILesson::IElement *>&       getElementsP();
    const QList<ILesson::IElement *>& getElements() const;

private:
    QList<ILesson::IElement *>    elements;
    QString                       title;
};

//! Provides an implementation of ILesson::IPage to be used by the plugin.
class LPage : public ILesson::IPage, public LItem
{
public:
    LPage();
    ~LPage() {}

    const Type              getType() const;
    const QString&          getTitle() const;
    void                    setTitle(const QString& title);

    const QList<IObject *>&   getObjects() const;
    void                    addObject(IObject *object);

private:
    QString             title;
    QList<IObject *>    objects;
};

//! Provides an implementation of ILesson::IPage::IObject to be used by the plugin.
class LObject : public ILesson::IPage::IObject
{
public:
    LObject();
    const QPointF&      getPosition() const;
    void                setPosition(const QPointF& pos);
    const QSizeF&       getSize() const;
    void                setSize(const QSizeF& size);
    const QString&      getType() const;
    void                setType(const QString& type);
    QWidget*            getWidget();
    void                setWidget(QWidget *widget);
    const QMap<QString, int>&    getRequiredFiles() const;
    void                addRequiredFile(QString fileName);
    const QString&      getParameters() const;
    void                setParameters(const QString& params);
    IController*        getController();
    void                setController(IController *ctrl);

private:
    IController         *ctrl;
    QPointF             position;
    QSizeF              size;
    QString             type;
    QString             params;
    QWidget*            widget;
    QMap<QString, int>  requiredFiles;
};

//! Provides an implementation of ILesson to be used by the plugin.
class Lesson : public ILesson, public LItem
{
public:
    Lesson();
    ~Lesson() {}
    const QString&          getTitle() const;
    void                    setTitle(const QString& title);
    const QList<IElement *>&  getElements() const;
    IElement*               addElement(IElement::Type type, const QString& title);
    IElement*               addElement(IElement::Type type, const QString& title, const ISection *section);

public:
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;
    int         rowCount(const QModelIndex &parent = QModelIndex()) const;
    int         columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant    data(const QModelIndex &index, int role = Qt::DisplayRole) const;

private:
    LSection*   findSection(QList<IElement *>& list, const ISection *section);
    void*       findNodeParent(const QList<ILesson::IElement *>& list, void *parent, const void* node) const;

private:
    QList<IElement *>  elements;
    QString  title;
    QModelIndex        invalidIdx;
};

#endif // LESSON_H
