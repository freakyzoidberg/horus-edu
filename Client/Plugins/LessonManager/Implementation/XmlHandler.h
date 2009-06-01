#ifndef XMLHANDLER_H
#define XMLHANDLER_H

#include <QtXml/QXmlDefaultHandler>
#include <QStack>
#include "Lesson.h"

class XmlHandler : public QXmlDefaultHandler
{
public:
    XmlHandler(Lesson *lesson);
    bool    startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts);
    bool    endElement(const QString &namespaceURI, const QString &localName, const QString &qName);

private:
    Lesson* lesson;
    bool hasLesson;
    QStack<ILesson::ISection*> sections;
    ILesson::IPage* currentPage;
};

#endif // XMLHANDLER_H
