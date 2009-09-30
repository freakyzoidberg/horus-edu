#include "LessonModel.h"

#include <QMimeData>
#include <iostream>

#include "../../../Common/UserData.h"
#include "Implementation/Lesson.h"
#include "ILessonDocument.h"

LessonModel::LessonModel(PluginManager* pluginManager)
{
    this->pluginManager = pluginManager;
	rootItem = qobject_cast<Data*>(pluginManager->findPlugin<TreeDataPlugin*>()->getNode(0));
	filePlugin = pluginManager->findPlugin<FileDataPlugin*>();
}

int LessonModel::columnCount ( const QModelIndex & parent) const
{
    return 1;
}

int LessonModel::rowCount ( const QModelIndex & parent) const
{
    if (!parent.isValid())
        return 1;

	QObject* data = (QObject*)(parent.internalPointer());
	int count = data->children().count();

	TreeData *tdata = qobject_cast<TreeData *>(data);
	if (tdata)
	{
		UserData* user = pluginManager->currentUser();
		QList<FileData*> files = filePlugin->getFilesInNodeAndUser(tdata, user);
		foreach (FileData* file, files)
		{
			if (file->mimeType() == "x-horus/x-lesson")
				count++;
		}
	}
	return count;
}

QVariant LessonModel::data ( const QModelIndex & index, int role) const
{
	if (!index.isValid() || role == Qt::BackgroundRole)
        return QVariant();
    QObject* obj = (QObject*)(index.internalPointer());
    Data *data = qobject_cast<Data *>(obj);
    if (data)
    {
       if (index.column() == 0 && role == Qt::DecorationRole)
            return data->data(0, role);
       return data->data(1, role);
    }
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

QModelIndex LessonModel::index ( int row, int column, const QModelIndex & parent ) const
{
    if ( ! parent.isValid())
        return createIndex(row, column, rootItem);

	QObject* data = (QObject*)(parent.internalPointer());
	if (row < data->children().count())
		return createIndex(row, column, data->children().at(row));
	int count = data->children().count();

	TreeData *tdata = qobject_cast<TreeData *>(data);
	if (tdata)
	{
		UserData* user = pluginManager->currentUser();
		QList<FileData*> files = filePlugin->getFilesInNodeAndUser(tdata, user);
		foreach (FileData* file, files)
		{
			if (file->mimeType() == "x-horus/x-lesson")
			{
				if (row == count)
				{
					Lesson *lesson = Lesson::createLesson(file);
					return createIndex(row, column, lesson);
				}
				count++;
			}
		}
	}
	qDebug() << "[LessonModel] too many rows there";
	return createIndex(row, column, ((QObject*)(parent.internalPointer()))->children().at(row));
}

QModelIndex LessonModel::parent ( const QModelIndex & index ) const
{
    QObject* obj = (QObject*)(index.internalPointer());

    if (obj == rootItem)
        return QModelIndex();

    if (obj->parent() == rootItem)
        return createIndex(0, 0, rootItem);

	Lesson* lesson = qobject_cast<Lesson *>(obj);
	if (lesson)
	{
		FileData *fdata = lesson->getFiledata();
		obj = fdata->node();
	}
	else
	{
		obj = obj->parent();
		lesson = qobject_cast<Lesson *>(obj);
		if (lesson)
		{
			UserData* user = pluginManager->currentUser();
			FileData* fdata = lesson->getFiledata();
			TreeData* tdata = fdata->node();
			int count = tdata->children().count();
			QList<FileData*> files = filePlugin->getFilesInNodeAndUser(tdata, user);
			foreach (FileData* file, files)
			{
				if (file->mimeType() == "x-horus/x-lesson")
				{
					if (file == fdata)
					{
						return createIndex(count, 0, lesson);
					}
					count++;
				}
			}
		}
	}

    return createIndex(obj->parent()->children().indexOf(obj), 0, obj);
}
