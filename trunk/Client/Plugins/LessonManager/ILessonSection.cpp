#include "ILessonSection.h"

ILessonSection::ILessonSection(ILesson *parent) : ILessonData(parent)
{
}

ILessonSection::ILessonSection(ILessonSection *parent) : ILessonData(parent)
{
}
