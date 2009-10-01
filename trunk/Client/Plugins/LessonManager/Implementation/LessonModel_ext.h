#ifndef LESSONMODEL_EXT_H
#define LESSONMODEL_EXT_H

#include "../LessonModel.h"
#include "../ILesson.h"
#include "../ILessonDocument.h"

class LessonModel_ext : public LessonModel
{
public:
	LessonModel_ext(PluginManager *manager);

	bool  createLesson(QModelIndex& idx);
	ILesson* getLesson(int id);
	ILessonDocument* getLessonDocument(int lessonId, int documentId);

private:
	ILessonDocument* findDoc(ILessonData* ldata, int documentId);
};

#endif // LESSONMODEL_EXT_H
