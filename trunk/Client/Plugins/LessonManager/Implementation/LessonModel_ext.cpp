#include "LessonModel_ext.h"
#include "../../../Common/FileData.h"

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
