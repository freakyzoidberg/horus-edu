#include "Lesson.h"
#include "LessonSection.h"
#include "LessonDocument.h"

Lesson::Lesson(FileData *parent) : ILesson(NULL), _currentData(NULL)
{
    xmlFile = parent->file();
    QXmlSimpleReader xmlReader;
    QXmlInputSource *source = new QXmlInputSource(xmlFile);
    xmlReader.setContentHandler(this);
    xmlReader.setErrorHandler(this);
    bool ok = xmlReader.parse(source);
    if (ok == false)
        qDebug() << "Error parsing metadata";
	_fileData = parent;
	if (icon == NULL)
		icon = new QIcon(":/Icons/LessonIcon.png");
}

QVariant Lesson::data(int column, int role) const
{
    if (role == Qt::DisplayRole)
        return QVariant(getTitle());
    else if (role == Qt::DecorationRole)
		return QVariant(*icon);
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
		else
			return false;
        if ((idx = atts.index("id")) != -1)
			document->setId(QVariant(atts.value(idx)).toInt());
		else
			return false;
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

QHash<FileData *, Lesson *> Lesson::lessons;

Lesson *Lesson::createLesson(FileData *data)
{
	if (lessons.contains(data))
		return *(lessons.find(data));
	Lesson *res = new Lesson(data);
	lessons.insert(data, res);
	return res;
}

QIcon *Lesson::icon = NULL;
