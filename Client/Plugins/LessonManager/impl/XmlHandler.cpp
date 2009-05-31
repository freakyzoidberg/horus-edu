#include <QDebug>
#include "XmlHandler.h"

XmlHandler::XmlHandler(Lesson *lesson) : lesson(lesson), hasLesson(false), currentElement(NULL)
{
}

bool XmlHandler::startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts)
{
    if (qName == "lesson")
    {
        if (atts.count() != 1 || atts.qName(0) != "title")
            return false;
        hasLesson = true;
        lesson->setTitle(atts.value(0));
    }
    else if (qName == "section")
    {
        if (!hasLesson || atts.count() != 1 || atts.qName(0) != "title")
            return false;
        if (currentElement == NULL)
            currentElement = lesson->addElement(ILesson::IElement::SECTION, atts.value(0));
        else
            currentElement = lesson->addElement(ILesson::IElement::SECTION, atts.value(0), dynamic_cast<ILesson::ISection *>(currentElement));
    }
    else if (qName == "page")
    {
        if (!hasLesson || atts.count() != 1 || atts.qName(0) != "title")
            return false;
        if (currentElement == NULL)
            lesson->addElement(ILesson::IElement::PAGE, atts.value(0));
        else
            lesson->addElement(ILesson::IElement::PAGE, atts.value(0), dynamic_cast<ILesson::ISection *>(currentElement));
    }
    return true;
}

bool XmlHandler::endElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts)
{
    if (qName == "lesson")
        hasLesson = false;
    return true;
}
