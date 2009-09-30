#include "LessonDocument.h"

LessonDocument::LessonDocument(ILessonSection *parent) : ILessonDocument(parent)
{
	if (icon == NULL)
		icon = new QIcon(":/Icons/DocumentIcon.png");
}

LessonDocument::LessonDocument(ILesson *parent) : ILessonDocument(parent)
{
}

QVariant LessonDocument::data(int column, int role) const
{
    if (role == Qt::DisplayRole)
        return QVariant(getTitle());
    else if (role == Qt::DecorationRole)
		return QVariant(*icon);
    return QVariant();
}

void	LessonDocument::setId(int id)
{
	this->_id = id;
}

int	LessonDocument::getId()
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

QIcon *LessonDocument::icon = NULL;
