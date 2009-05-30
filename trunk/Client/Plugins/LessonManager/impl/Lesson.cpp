#include "Lesson.h"

LSection::LSection()
{

}

const ILesson::IElement::Type                      LSection::getType() const
{
    return ILesson::IElement::SECTION;
}

const QString&                  LSection::getTitle() const
{
    return title;
}

void                            LSection::setTitle(const QString& title)
{
    this->title = title;
}

QList<ILesson::IElement *>&       LSection::getElementsP()
{
    return elements;
}

const QList<ILesson::IElement *>& LSection::getElements() const
{
    return elements;
}

LPage::LPage()
{

}

const ILesson::IElement::Type              LPage::getType() const
{
    return ILesson::IElement::PAGE;
}

const QString&          LPage::getTitle() const
{
    return title;
}

void                    LPage::setTitle(const QString& title)
{
    this->title = title;
}

const QList<ILesson::IPage::IObject *>&   LPage::getObjects() const
{
    return objects;
}

void                    LPage::addObject(ILesson::IPage::IObject *object)
{
    objects.push_back(object);
}

Lesson::Lesson()
{
}

const QString&          Lesson::getTitle() const
{
    return title;
}

void                    Lesson::setTitle(const QString& title)
{
    this->title = title;
}

const QList<ILesson::IElement *>&  Lesson::getElements() const
{
    return elements;
}

ILesson::IElement* Lesson::addElement(ILesson::IElement::Type type, const QString& title)
{
    if (type == ILesson::IElement::PAGE)
    {
        elements.push_back(new LPage());
    }
    else if (type == ILesson::IElement::SECTION)
    {
        elements.push_back(new LSection());
    }
    elements.last()->setTitle(title);
    return elements.last();
}

ILesson::IElement* Lesson::addElement(ILesson::IElement::Type type, const QString& title, const ILesson::ISection *section)
{
    LSection* sec = findSection(elements, section);
    if (sec == NULL)
        return NULL;
    if (type == ILesson::IElement::PAGE)
    {
        sec->getElementsP().push_back(new LPage());
    }
    else if (type == ILesson::IElement::SECTION)
    {
        sec->getElementsP().push_back(new LSection());
    }
    sec->getElementsP().last()->setTitle(title);
    return sec->getElementsP().last();
}

LSection* Lesson::findSection(QList<ILesson::IElement *>& list, const ILesson::ISection *section)
{
    QList<ILesson::IElement *>::iterator it = list.begin();
    LSection *sec;
    while (it != list.end())
    {
        if (*it == section)
            return dynamic_cast<LSection *>(*it);
        else if ((sec = dynamic_cast<LSection *>(*it)) != NULL)
        {
            LSection *res = findSection(sec->getElementsP(), section);
            if (res != NULL)
                return res;
        }
        it++;
    }
    return NULL;
}
