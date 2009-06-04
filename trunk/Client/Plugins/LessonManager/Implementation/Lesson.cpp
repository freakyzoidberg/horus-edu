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

/**********************************************************************/
/**********************************************************************/
/**********************************************************************/

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

/**********************************************************************/
/**********************************************************************/
/**********************************************************************/

LObject::LObject() : ctrl(NULL), widget(NULL)
{
}

const QPointF& LObject::getPosition() const
{
    return position;
}

void LObject::setPosition(const QPointF& pos)
{
    this->position = pos;
}

const QSizeF& LObject::getSize() const
{
    return size;
}

void LObject::setSize(const QSizeF& size)
{
    this->size = size;
}

const QString& LObject::getType() const
{
    return type;
}

void LObject::setType(const QString& type)
{
    this->type = type;
}

QWidget* LObject::getWidget()
{
    return widget;
}

void LObject::setWidget(QWidget *widget)
{
    this->widget = widget;
}

const QMap<QString, int>& LObject::getRequiredFiles() const
{
    return requiredFiles;
}

void LObject::addRequiredFile(QString fileName)
{
    requiredFiles.insert(fileName, -1);
}

const QString&      LObject::getParameters() const
{
    return params;
}

void                LObject::setParameters(const QString& params)
{
    this->params = params;
}

ILesson::IPage::IObject::IController* LObject::getController()
{
    return ctrl;
}

void LObject::setController(ILesson::IPage::IObject::IController *ctrl)
{
    this->ctrl = ctrl;
}

/**********************************************************************/
/**********************************************************************/
/**********************************************************************/

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

void* Lesson::findNodeParent(const QList<ILesson::IElement *>& list, void *parent, const void* node) const
{
    QList<ILesson::IElement *>::const_iterator it = list.begin();
    LSection *sec;
    while (it != list.end())
    {
        if (*it == node)
            return parent;
        else if ((sec = dynamic_cast<LSection *>(*it)) != NULL)
        {
            void *res = findNodeParent(sec->getElementsP(), sec, node);
            if (res != NULL)
                return res;
        }
        it++;
    }
    return NULL;
}

QModelIndex Lesson::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        if (row == 0)
            return createIndex(row, column, parent.internalPointer());
        LSection* section = dynamic_cast<LSection *>((LItem *)parent.internalPointer());
        return createIndex(row, column, section->getElements().at(row));
    }
    if (row == 0)
        createIndex(row, column, (void *)this);
    return createIndex(row, column, elements.at(row));
}

QModelIndex Lesson::parent(const QModelIndex &child) const
{
    void *ptr = child.internalPointer();
    if (child == invalidIdx || child.internalPointer() == this)
        return invalidIdx;
    void *node = findNodeParent(elements, (void *)this, child.internalPointer());
    if (node != NULL)
        return createIndex(0, 0, node);
    return invalidIdx;
}

int         Lesson::rowCount(const QModelIndex &parent) const
{
    Lesson *lesson = NULL;
    LSection *section = NULL;
    if (parent == invalidIdx)
        return 0;
    if ((lesson = dynamic_cast<Lesson *>((LItem *)parent.internalPointer())) != NULL)
        return lesson->getElements().count();
    else if ((section = dynamic_cast<LSection *>((LItem *)parent.internalPointer())) != NULL)
        return section->getElements().count();
    return 0;
}

int         Lesson::columnCount(const QModelIndex &parent) const
{
    if (parent == invalidIdx)
        return 0;
    return 1;
}

QVariant    Lesson::data(const QModelIndex &index, int role) const
{
    return QVariant();
}
