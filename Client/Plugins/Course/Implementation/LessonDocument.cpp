#include "LessonDocument.h"

LessonDocument::LessonDocument(QObject *parent, int id, QString title, QString _type, QString _content, QHash<QString, QVariant> _parameters) : ILessonDocument(parent)
{
	this->_title = title;
	this->type = _type;
	this->content = _content;
	this->parameters = _parameters;
	this->_id = id;
}

QVariant LessonDocument::data(int column, int role) const
{
    if (role == Qt::DisplayRole)
        return QVariant("Document");
    return QVariant();
}

void	LessonDocument::setId(int id)
{
	this->_id = id;
}

int		LessonDocument::getId()
{
	return (this->_id);
}

QString LessonDocument::getContent() const
{
        return (this->content);
}

void	LessonDocument::setContent(QString _content)
{
        this->content = _content;
}

QHash<QString, QVariant>	&LessonDocument::getParameters()
{
        return (this->parameters);
}

QString LessonDocument::getType() const
{
    return type;
}

void LessonDocument::setType(QString type)
{
    this->type = type;
}
