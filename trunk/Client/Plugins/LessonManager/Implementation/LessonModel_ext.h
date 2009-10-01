#ifndef LESSONMODEL_EXT_H
#define LESSONMODEL_EXT_H

#include "../LessonModel.h"

class LessonModel_ext : public LessonModel
{
public:
	LessonModel_ext(PluginManager *manager);

	bool  createLesson(QModelIndex& idx);
};

#endif // LESSONMODEL_EXT_H
