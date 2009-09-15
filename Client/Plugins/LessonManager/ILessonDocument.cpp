#include "ILessonDocument.h"

ILessonDocument::ILessonDocument(ILesson *parent) : ILessonData(parent)
{
}

ILessonDocument::ILessonDocument(ILessonSection *parent) : ILessonData(parent)
{
}

QString ILessonDocument::getContent() const
{
	return (this->content);
}

void	ILessonDocument::setContent(QString _content)
{
	this->content = _content;
}

QHash<QVariant, QVariant>	&ILessonDocument::getParameters()
{
	return (this->parameters);
}
