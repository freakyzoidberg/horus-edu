#include "Lesson.h"
#include "LessonSection.h"
#include "LessonDocument.h"

Lesson::Lesson(FileData *parent) : ILesson(parent), _currentData(NULL), icon(":/Icons/LessonIcon.png")
{
#ifdef TEST_METADATA
    xmlFile = new QFile("../Plugins/LessonManager/metadata_test.xml");
#else
    xmlFile = parent->file();
#endif
    QXmlSimpleReader xmlReader;
    QXmlInputSource *source = new QXmlInputSource(xmlFile);
    xmlReader.setContentHandler(this);
    xmlReader.setErrorHandler(this);
    bool ok = xmlReader.parse(source);
    if (ok == false)
        qDebug() << "Error parsing metadata";
}

QVariant Lesson::data(int column, int role) const
{
    if (role == Qt::DisplayRole)
        return QVariant("Lesson");
    else if (role == Qt::DecorationRole)
        return QVariant(icon);
    return QVariant();
}

bool    Lesson::startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts)
{
    int idx = -1;
    if (qName == "Lesson" && _currentData == NULL)
    {
        _currentData = this;
    }
    else if (qName == "Section" && _currentData)
    {
        Lesson *lesson = qobject_cast<Lesson *>(_currentData);
        LessonSection *section = qobject_cast<LessonSection *>(_currentData);
        if (lesson)
            _currentData = new LessonSection(lesson);
        else if (section)
            _currentData = new LessonSection(section);
        else
            return false;
    }
    else if (qName == "Document" && _currentData)
    {
        Lesson *lesson = qobject_cast<Lesson *>(_currentData);
        LessonSection *section = qobject_cast<LessonSection *>(_currentData);
        if (lesson)
            _currentData = new LessonDocument(lesson);
        else if (section)
            _currentData = new LessonDocument(section);
        else
            return false;
        LessonDocument *document = qobject_cast<LessonDocument *>(_currentData);
        if ((idx = atts.index("type")) != -1)
            document->setType(atts.value(idx));
        for (int i = 0; i < atts.count(); ++i)
        {
            if (atts.value(i) != "title" && atts.value(i) != "type")
                document->getParameters().insert(atts.qName(i), QVariant(atts.value(i)));
        }
        startCDATA();
    }
    else
    {
        return false;
    }
    if ((idx = atts.index("title")) != -1)
        _currentData->setTitle(atts.value(idx));
    return true;
}

bool    Lesson::endElement(const QString &namespaceURI, const QString &localName, const QString &qName)
{
    if (_currentData)
    {
        if (qobject_cast<LessonDocument *>(_currentData))
            endCDATA();
        _currentData = qobject_cast<ILessonData *>(_currentData->parent());
    }
    return true;
}

bool    Lesson::characters(const QString& ch)
{
    LessonDocument* document = qobject_cast<LessonDocument*>(_currentData);
    if (document)
        document->setContent(ch);
    return true;
}
