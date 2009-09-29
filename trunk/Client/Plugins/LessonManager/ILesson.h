#ifndef ILESSON_H
#define ILESSON_H

#include "../../../Common/FileData.h"
#include "ILessonData.h"

class ILesson : public ILessonData
{
    Q_OBJECT

public:
	inline ILesson(FileData *parent) : ILessonData(parent) {}
    virtual ~ILesson() {}
};

#endif // ILESSON_H
