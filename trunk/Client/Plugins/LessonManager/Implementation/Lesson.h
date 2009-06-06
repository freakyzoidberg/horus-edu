#ifndef LESSON_H
#define LESSON_H

#include <QMap>
#include <QString>
#include <QIcon>
#include "../ILesson.h"

class LElement : virtual public ILesson::IElement
{
public:
    LElement(LElement *parent);

    LElement    *getParent();
    const QString&  getTitle() const;
    void            setTitle(const QString& title);

private:
    LElement    *parent;
    QString     title;
};

//! Provides an implementation of ILesson::ISection to be used by the plugin.
class LSection : public ILesson::ISection, public LElement
{
public:
    LSection(LElement *parent);
    ~LSection() {}

    const Type                        getType() const;
    QList<ILesson::IElement *>&       getElementsP();
    const QList<ILesson::IElement *>& getElements() const;

private:
    QList<ILesson::IElement *>    elements;
};

//! Provides an implementation of ILesson::IPage to be used by the plugin.
class LPage : public ILesson::IPage, public LElement
{
public:
    LPage(LElement *parent);
    ~LPage() {}

    const Type              getType() const;
    const QList<IObject *>& getObjects() const;
    void                    addObject(IObject *object);

private:
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
    const QList<quint32>&    getRequiredFiles() const;
    void                addRequiredFile(quint32 id);
    const QString&      getParameters() const;
    void                setParameters(const QString& params);
    const QString&      getContent() const;
    void                setContent(const QString& content);
    IController*        getController();
    void                setController(IController *ctrl);

private:
    IController         *ctrl;
    QPointF             position;
    QSizeF              size;
    QString             type;
    QString             params;
    QString             content;
    QWidget*            widget;
    QList<quint32>      requiredFiles;
};

//! Provides an implementation of ILesson to be used by the plugin.
class Lesson : public ILesson
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
    QVariant    headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

private:
    LSection*   findSection(QList<IElement *>& list, const ISection *section);

private:
    QList<IElement *>  elements;
    QString  title;

    static QIcon    lessonIcon;
    static QIcon    sectionIcon;
    static QIcon    pageIcon;
};

#endif // LESSON_H
