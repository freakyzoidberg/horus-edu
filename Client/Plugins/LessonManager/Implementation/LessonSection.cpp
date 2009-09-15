#include "LessonSection.h"

LessonSection::LessonSection(ILessonSection *parent) : ILessonSection(parent), icon(":/Icons/SectionIcon.png")
{
}

LessonSection::LessonSection(ILesson *parent) : ILessonSection(parent)
{
}

QVariant LessonSection::data(int column, int role) const
{
    if (role == Qt::DisplayRole)
        return QVariant("Section");
    else if (role == Qt::DecorationRole)
        return QVariant(icon);
    return QVariant();
}
