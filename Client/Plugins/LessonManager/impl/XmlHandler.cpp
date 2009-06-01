#include <QDebug>
#include "XmlHandler.h"

XmlHandler::XmlHandler(Lesson *lesson) : lesson(lesson), hasLesson(false), currentPage(NULL)
{
}

bool XmlHandler::startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts)
{
    if (qName == "lesson")
    {
        if (atts.count() < 1 || atts.qName(0) != "title")
            return false;
        hasLesson = true;
        lesson->setTitle(atts.value(0));
    }
    else if (qName == "section")
    {
        if (!hasLesson || atts.count() < 1 || atts.qName(0) != "title")
            return false;
        if (sections.empty())
            sections.push(dynamic_cast<ILesson::ISection*>(lesson->addElement(ILesson::IElement::SECTION, atts.value(0))));
        else
            sections.push(dynamic_cast<ILesson::ISection*>(lesson->addElement(ILesson::IElement::SECTION, atts.value(0), sections.top())));
    }
    else if (qName == "page")
    {
        if (!hasLesson || atts.count() < 1 || atts.qName(0) != "title")
            return false;
        if (sections.empty())
            currentPage = dynamic_cast<ILesson::IPage*>(lesson->addElement(ILesson::IElement::PAGE, atts.value(0)));
        else
            currentPage = dynamic_cast<ILesson::IPage*>(lesson->addElement(ILesson::IElement::PAGE, atts.value(0), sections.top()));
    }
    else if (qName == "object")
    {
        if (currentPage == NULL || atts.count() < 1 || atts.qName(0) != "type")
            return false;
        LObject* obj = new LObject();
        obj->setType(atts.value(0));
        if (atts.count() > 1)
        {
            for (int i = 1; i < atts.count(); ++i)
            {
                if (atts.qName(i) == "position")
                {
                    QStringList list = atts.value(i).split(',');
                    obj->setPosition(QPointF(list.at(0).toFloat(), list.at(1).toFloat()));
                }
                else if (atts.qName(i) == "size")
                {
                    QStringList list = atts.value(i).split(',');
                    obj->setSize(QSizeF(list.at(0).toFloat(), list.at(1).toFloat()));
                }
            }
        }

        currentPage->addObject(obj);
    }
    return true;
}

bool XmlHandler::endElement(const QString &namespaceURI, const QString &localName, const QString &qName)
{
    if (qName == "lesson")
        hasLesson = false;
    else if (qName == "section")
        sections.pop();
    else if (qName == "page")
        currentPage = NULL;
    return true;
}
