#ifndef LESSONSECTION_H
#define LESSONSECTION_H

#include <QIcon>

#include "../ILessonSection.h"

class LessonSection : public ILessonSection
{
    Q_OBJECT

public:
    LessonSection(ILessonSection *parent);
    LessonSection(ILesson *parent);

    QVariant data(int column, int role) const;
    QIcon icon;
};

#endif // LESSONSECTION_H
