#ifndef ILESSONSECTION_H
#define ILESSONSECTION_H

#include <QObject>

#include "ILessonData.h"
#include "ILesson.h"
#include "ILessonSection.h"

class ILessonSection : public ILessonData
{
    Q_OBJECT

public:
    ILessonSection(ILesson *parent);
    ILessonSection(ILessonSection *parent);
};

#endif // ILESSONSECTION_H
