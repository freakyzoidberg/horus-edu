/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
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
			FileData *fdata = filePlugin->createFile(data);
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
	return Lesson::createLesson(filePlugin->file(id), pluginManager);
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
