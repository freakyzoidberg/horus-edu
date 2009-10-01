#include "LessonSection.h"

LessonSection::LessonSection(ILessonSection *parent) : ILessonSection(parent)
{
	if (icon == NULL)
		icon = new QIcon(":/Icons/SectionIcon.png");
}

LessonSection::LessonSection(ILesson *parent) : ILessonSection(parent)
{
}

QVariant LessonSection::data(int column, int role) const
{
    if (role == Qt::DisplayRole)
        return QVariant(getTitle());
    else if (role == Qt::DecorationRole)
		return QVariant(*icon);
    return QVariant();
}

QIcon *LessonSection::icon = NULL;
