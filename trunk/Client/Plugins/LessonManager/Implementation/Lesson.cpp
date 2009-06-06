#include "Lesson.h"

LElement::LElement(LElement *parent) : parent(parent)
{
}

LElement    *LElement::getParent()
{
    return parent;
}

const QString&          LElement::getTitle() const
{
    return title;
}

void                    LElement::setTitle(const QString& title)
{
    this->title = title;
}

/**********************************************************************/
/**********************************************************************/
/**********************************************************************/

LSection::LSection(LElement *parent) : LElement(parent)
{

}

const ILesson::IElement::Type                      LSection::getType() const
{
    return ILesson::IElement::SECTION;
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

LPage::LPage(LElement *parent) : LElement(parent)
{

}

const ILesson::IElement::Type              LPage::getType() const
{
    return ILesson::IElement::PAGE;
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

const QList<quint32>& LObject::getRequiredFiles() const
{
    return requiredFiles;
}

void LObject::addRequiredFile(quint32 id)
{
    requiredFiles.push_back(id);
}

const QString&      LObject::getParameters() const
{
    return params;
}

void                LObject::setParameters(const QString& params)
{
    this->params = params;
}

IController* LObject::getController()
{
    return ctrl;
}

void LObject::setController(IController *ctrl)
{
    this->ctrl = ctrl;
}

const QString&      LObject::getContent() const
{
    return content;
}

void                LObject::setContent(const QString& content)
{
    this->content = content;
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
        elements.push_back(new LPage(NULL));
    }
    else if (type == ILesson::IElement::SECTION)
    {
        elements.push_back(new LSection(NULL));
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
        sec->getElementsP().push_back(new LPage(sec));
    }
    else if (type == ILesson::IElement::SECTION)
    {
        sec->getElementsP().push_back(new LSection(sec));
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
        {
            return dynamic_cast<LSection *>(*it);
        }
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

QModelIndex Lesson::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        if (parent.internalPointer() == this)
            return createIndex(row, column, elements.at(row));
        LSection* section = dynamic_cast<LSection *>(static_cast<ILesson::IElement *>(parent.internalPointer()));
        if (section != NULL)
            return createIndex(row, column, section->getElements().at(row));
        return QModelIndex();
    }
    if (row == 0)
        return createIndex(row, column, (void *)this);
    return QModelIndex();
}

QModelIndex Lesson::parent(const QModelIndex &child) const
{
    if (!child.isValid() || child.internalPointer() == this)
        return QModelIndex();
    LElement *elem = dynamic_cast<LElement *>(static_cast<ILesson::IElement *>(child.internalPointer()));
    if (elem != NULL)
    {
        if (elem->getParent() != NULL)
        {
            int i;
            if (elem->getParent()->getParent() != NULL)
            {
                LSection *section = static_cast<LSection *>(elem->getParent()->getParent());
                for (i = 0; i < section->getElementsP().count(); ++i)
                {
                    if (section->getElementsP().at(i) == dynamic_cast<ILesson::IElement *>((elem->getParent())))
                        break;
                }
                if (i < section->getElementsP().count())
                    return createIndex(i, 0, dynamic_cast<ILesson::IElement *>((elem->getParent())));
                return QModelIndex();
            }
            else
            {
                for (i = 0; i < elements.count(); ++i)
                {
                    if (elements.at(i) == dynamic_cast<ILesson::IElement *>((elem->getParent())))
                        break;
                }
                if (i < elements.count())
                    return createIndex(i, 0, dynamic_cast<ILesson::IElement *>((elem->getParent())));
            }
        }
        else
        {
            return createIndex(0, 0, (void *)this);
        }
    }
    return QModelIndex();
}

int         Lesson::rowCount(const QModelIndex &parent) const
{
    LSection *section = NULL;
    if (!parent.isValid())
        return 1;
    if (parent.internalPointer() == this)
        return elements.count();
    else if ((section = dynamic_cast<LSection *>(static_cast<ILesson::IElement *>(parent.internalPointer()))) != NULL)
        return section->getElements().count();
    return 0;
}

int         Lesson::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant    Lesson::data(const QModelIndex &index, int role) const
{
    LSection *section = NULL;
    LPage *page = NULL;
    if (role == Qt::DisplayRole)
    {
        if (index.internalPointer() == this)
            return QVariant(title);
        else if ((section = dynamic_cast<LSection *>(static_cast<ILesson::IElement *>(index.internalPointer()))) != NULL)
            return QVariant(section->getTitle());
        else if ((page = dynamic_cast<LPage *>(static_cast<ILesson::IElement *>(index.internalPointer()))) != NULL)
            return QVariant(page->getTitle());
    }
    else if (role == Qt::DecorationRole)
    {
        if (index.internalPointer() == this)
            return QVariant(QVariant::Icon, &Lesson::lessonIcon);
        else if ((section = dynamic_cast<LSection *>(static_cast<ILesson::IElement *>(index.internalPointer()))) != NULL)
            return QVariant(QVariant::Icon, &Lesson::sectionIcon);
        else if ((page = dynamic_cast<LPage *>(static_cast<ILesson::IElement *>(index.internalPointer()))) != NULL)
            return QVariant(QVariant::Icon, &Lesson::pageIcon);
    }
    else if (role == Qt::UserRole)
    {
        if ((page = dynamic_cast<LPage *>(static_cast<ILesson::IElement *>(index.internalPointer()))) != NULL)
        {
            QVariant v;
            v.setValue(static_cast<ILesson::IPage *>(page));
            return v;
        }
    }
    return QVariant();
}

QVariant    Lesson::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (section == 0 && (orientation == Qt::Horizontal || orientation == Qt::Vertical) && role == Qt::DisplayRole)
    {
        return QVariant(title);
    }
    return QVariant();
}

QIcon    Lesson::lessonIcon(":/Icons/LessonIcon.png");
QIcon    Lesson::sectionIcon(":/Icons/SectionIcon.png");
QIcon    Lesson::pageIcon(":/Icons/PageIcon.png");
