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
#include "LessonModel.h"

#include <QMimeData>

#include "../../../Common/UserData.h"
#include "Implementation/Lesson.h"
#include "ILessonDocument.h"

LessonModel::LessonModel(PluginManager* pluginManager)
{
    this->pluginManager = pluginManager;
	filePlugin = pluginManager->findPlugin<FileDataPlugin*>();
	foreach (Data* data, filePlugin->allDatas())
	{
		FileData* file = static_cast<FileData*>(data);
		if (file->mimeType() == "x-horus/x-lesson" && file->node()->canAccess(pluginManager->currentUser()))
		{
			rootItems.append(file);
		}
	}
}

int LessonModel::columnCount ( const QModelIndex &) const
{
    return 1;
}

int LessonModel::rowCount ( const QModelIndex & parent) const
{
    if (!parent.isValid())
	{
        return rootItems.count();
	}

	QObject* obj = (QObject*)(parent.internalPointer());
	return obj->children().count();
}

QVariant LessonModel::data ( const QModelIndex & index, int role) const
{
	if (!index.isValid() || role == Qt::BackgroundRole)
        return QVariant();
    QObject* obj = (QObject*)(index.internalPointer());
    Data *data = qobject_cast<Data *>(obj);
    if (data)
	   return data->data(index.column(), role);
    else
    {
       ILessonData* ldata = qobject_cast<ILessonData *>(obj);
       if (ldata)
		   return ldata->data(0, role);
    }
    return QVariant();
}

Qt::ItemFlags LessonModel::flags( const QModelIndex & index) const
{
	Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);
    if (!index.isValid())
        return (defaultFlags);
    QObject* obj = (QObject*)(index.internalPointer());
    ILessonDocument *doc = qobject_cast<ILessonDocument *>(obj);
    if (doc)
        return (defaultFlags | Qt::ItemIsDragEnabled);
    else
        return (defaultFlags);
}

QStringList LessonModel::mimeTypes() const
{
    QStringList types;
    types << "application/vnd.horus.lessondocument.list";
    return (types);
}

QMimeData *LessonModel::mimeData(const QModelIndexList &indexes) const
{
	QMimeData *mimeData = new QMimeData();
	QByteArray encodedData;
	QDataStream stream(&encodedData, QIODevice::WriteOnly);

	foreach (QModelIndex index, indexes)
	{
		if (index.isValid())
		{
			QObject* obj = (QObject*)(index.internalPointer());
			ILessonDocument *doc = qobject_cast<ILessonDocument *>(obj);
			if (doc)
			{
				QObject* par = obj;
				do
				{
					par = par->parent();
				}
				while (par && !qobject_cast<ILesson *>(par));

				ILesson *lesson = qobject_cast<ILesson *>(par);
				if (!lesson)
				{
					qWarning() << "Lesson's document has no lesson";
					stream << -1;
				}
				else
				{
					stream << lesson->getId();
				}
				stream << doc->getId();
				stream << doc->getTitle();
				stream << doc->getType();
				stream << doc->getContent();
				QHash<QString, QVariant> map = doc->getParameters();
				stream << map.size();
				QHash<QString, QVariant>::const_iterator i = map.constBegin();
				while (i != map.constEnd())
				{
					stream << i.key() << i.value();
					++i;
				}
			}
		}
	}
	mimeData->setData("application/vnd.horus.lessondocument.list", encodedData);
	return (mimeData);
}

QModelIndex LessonModel::index(int row, int column, const QModelIndex & parent) const
{
    if (!parent.isValid())
	{
		Lesson *lesson = Lesson::createLesson(rootItems[row], pluginManager);
        return createIndex(row, column, lesson);
	}

	QObject* obj = (QObject*)(parent.internalPointer());
	return createIndex(row, column, obj->children().at(row));
}

QModelIndex LessonModel::parent(const QModelIndex &index) const
{
    QObject* obj = (QObject*)(index.internalPointer());

	Lesson* lesson = qobject_cast<Lesson *>(obj);
	if (lesson)
	{
		return QModelIndex();
	}

	lesson = qobject_cast<Lesson *>(obj->parent());
	if (lesson)
	{
		return createIndex(rootItems.indexOf(lesson->getFiledata()), 0, lesson);
	}

	QObject* parent = obj->parent();
	return createIndex(parent->parent()->children().indexOf(parent), 0, parent);
}
