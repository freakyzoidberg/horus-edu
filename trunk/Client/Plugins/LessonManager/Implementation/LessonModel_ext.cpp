#include "LessonModel_ext.h"
#include "Lesson.h"
#include "../../../../Common/FileData.h"

LessonModel_ext::LessonModel_ext(PluginManager *manager) : LessonModel(manager)
{
}

bool LessonModel_ext::createLesson(QModelIndex& index)
{
	if (index.isValid())
	{
		TreeData* data = qobject_cast<TreeData *>(static_cast<QObject *>(index.internalPointer()));
		if (data && data->type() == "SUBJECT")
		{
			int count = rowCount(index);
			beginInsertRows(index, count, count);
			FileData *fdata = filePlugin->createNewFile(data);
			fdata->setMimeType("x-horus/x-lesson");
			fdata->create();
			endInsertRows();
			return true;
		}
	}
	return false;
}

ILesson* LessonModel_ext::getLesson(int id)
{
	return Lesson::createLesson(filePlugin->getFile(id));
}

ILessonDocument* LessonModel_ext::getLessonDocument(int lessonId, int documentId)
{
	ILesson* lesson = getLesson(lessonId);
	return findDoc(lesson, documentId);
}

ILessonDocument* LessonModel_ext::findDoc(ILessonData* ldata, int documentId)
{
	foreach (QObject* child, ldata->children())
	{
		ILessonSection* section = qobject_cast<ILessonSection *>(child);
		if (section)
		{
			ILessonDocument* doc = findDoc(section, documentId);
			if (doc)
				return doc;
		}
		ILessonDocument* document = qobject_cast<ILessonDocument *>(child);
		if (document && document->getId() == documentId)
			return document;
	}
	return NULL;
}
