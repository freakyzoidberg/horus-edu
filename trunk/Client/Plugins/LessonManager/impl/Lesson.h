#ifndef LESSON_H
#define LESSON_H

#include "../ILesson.h"

class LSection : public ILesson::ISection
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
    QString     title;
};

class LPage : public ILesson::IPage
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
    QString     title;
    QList<IObject *>          objects;
};

class LObject : public ILesson::IPage::IObject
{

};

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

private:
    LSection*               findSection(QList<IElement *>& list, const ISection *section);

private:
    QList<IElement *>  elements;
    QString  title;
};

#endif // LESSON_H
