#ifndef LESSON_H
#define LESSON_H

#include <QXmlDefaultHandler>
#include <QIcon>

#include "../ILessonData.h"
#include "../ILesson.h"

//#ifndef TEST_METADATA
//# define TEST_METADATA
//#endif

class Lesson : public ILesson, public QXmlDefaultHandler
{
    Q_OBJECT

public:
    Lesson(FileData *parent);

    QVariant data(int column, int role) const;

    bool    startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts);
    bool    endElement(const QString &namespaceURI, const QString &localName, const QString &qName);
    bool    characters(const QString& ch);

private:
    QFile *xmlFile;
    ILessonData *_currentData;
    QIcon icon;
};

#endif // LESSON_H
