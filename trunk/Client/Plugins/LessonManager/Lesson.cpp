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

QList<LElement *>&       LSection::getElementsP()
{
    return elements;
}

const QList<LElement *>& LSection::getElements() const
{
    return elements;
}

/**********************************************************************/
/**********************************************************************/
/**********************************************************************/

LObject::LObject(LElement *parent) : LElement(parent), ctrl(NULL), widget(NULL)
{
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

const QList<LElement *>&  Lesson::getElements() const
{
    return elements;
}

void Lesson::addElement(LElement *element)
{
    elements.push_back(element);
}

QIcon    Lesson::lessonIcon(":/Icons/LessonIcon.png");
QIcon    Lesson::sectionIcon(":/Icons/SectionIcon.png");
QIcon    Lesson::pageIcon(":/Icons/PageIcon.png");
