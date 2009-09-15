#ifndef ILESSON_H
#define ILESSON_H

#include "../../../Common/FileData.h"
#include "ILessonData.h"

class ILesson : public ILessonData
{
    Q_OBJECT

public:
    ILesson(FileData *parent);
    virtual ~ILesson() {}
};

#endif // ILESSON_H
