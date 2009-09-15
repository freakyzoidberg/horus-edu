#ifndef ILESSONDOCUMENT_H
#define ILESSONDOCUMENT_H

#include <QObject>

#include "ILessonData.h"
#include "ILesson.h"
#include "ILessonSection.h"

class IController;

class ILessonDocument : public ILessonData
{
    Q_OBJECT

public:
    ILessonDocument(ILesson *parent);
    ILessonDocument(ILessonSection *parent);
};

#endif // ILESSONDOCUMENT_H
