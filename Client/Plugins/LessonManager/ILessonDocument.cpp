#include "ILessonDocument.h"

ILessonDocument::ILessonDocument(ILesson *parent) : ILessonData(parent)
{
}

ILessonDocument::ILessonDocument(ILessonSection *parent) : ILessonData(parent)
{
}
