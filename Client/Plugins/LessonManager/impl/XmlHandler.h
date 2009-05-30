#ifndef XMLHANDLER_H
#define XMLHANDLER_H

#include <QtXml/QXmlDefaultHandler>
#include "Lesson.h"

class XmlHandler : public QXmlDefaultHandler
{
public:
    XmlHandler(Lesson *lesson);
    bool    startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts);
    bool    endElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts);

private:
    Lesson              *lesson;
    bool                hasLesson;
    ILesson::IElement   *currentElement;
};

#endif // XMLHANDLER_H
