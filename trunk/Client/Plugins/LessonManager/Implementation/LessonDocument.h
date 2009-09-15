#ifndef LESSONDOCUMENT_H
#define LESSONDOCUMENT_H

#include <QIcon>

#include "../ILessonDocument.h"

class LessonDocument : public ILessonDocument
{
    Q_OBJECT

public:
    LessonDocument(ILessonSection *parent);
    LessonDocument(ILesson *parent);

    QVariant data(int column, int role) const;
    QIcon icon;
};

#endif // LESSONDOCUMENT_H
