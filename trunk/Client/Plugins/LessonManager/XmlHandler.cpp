#include <QDebug>
#include "XmlHandler.h"

XmlHandler::XmlHandler(Lesson *lesson) : lesson(lesson), hasLesson(false), currentObject(NULL)
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

    }
    else if (qName == "object")
    {
        if (atts.count() < 1 || atts.qName(0) != "type")
            return false;
        LObject* obj = new LObject(NULL);
        obj->setType(atts.value(0));
        startCDATA();
        if (atts.count() > 1)
        {
            for (int i = 1; i < atts.count(); ++i)
            {
                if (atts.qName(i) == "parameters")
                {
                    obj->setParameters(atts.value(i));
                }
                else if (atts.qName(i) == "requirements")
                {
                    QStringList ids = atts.value(i).split(',');
                    for (int j = 0; j < ids.count(); ++j)
                         obj->addRequiredFile(ids.at(j).toUInt());
                }
            }
        }
        currentObject = obj;
        currentSection->getElementsP().push_back(obj);
    }
    return true;
}

bool XmlHandler::endElement(const QString &namespaceURI, const QString &localName, const QString &qName)
{
    if (qName == "lesson")
        hasLesson = false;
    else if (qName == "section")
        sections.pop();
    else if (qName == "object")
    {
        endCDATA();
        currentObject = NULL;
    }
    return true;
}

bool    XmlHandler::characters(const QString& ch)
{
    if (currentObject != NULL)
        currentObject->setContent(ch);
    return (true);
}
