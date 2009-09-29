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
	inline ILessonSection(ILesson *parent) : ILessonData(parent) {}
	inline ILessonSection(ILessonSection *parent) : ILessonData(parent) {}
};

#endif // ILESSONSECTION_H
