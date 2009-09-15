#include "LessonDocument.h"

LessonDocument::LessonDocument(ILessonSection *parent) : ILessonDocument(parent), icon(":/DocumentIcon.png")
{
}

LessonDocument::LessonDocument(ILesson *parent) : ILessonDocument(parent)
{
}

QVariant LessonDocument::data(int column, int role) const
{
    if (role == Qt::DisplayRole)
        return QVariant("Document");
    else if (role == Qt::DecorationRole)
        return QVariant(icon);
    return QVariant();
}
