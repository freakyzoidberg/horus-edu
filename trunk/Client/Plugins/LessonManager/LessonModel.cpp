#include "LessonModel.h"

#include <QMimeData>

#include "../../../Common/UserData.h"
#include "Implementation/Lesson.h"
#include "ILessonDocument.h"

LessonModel::LessonModel(PluginManager* pluginManager)
{
    this->pluginManager = pluginManager;
	rootItem = qobject_cast<Data*>(pluginManager->findPlugin<TreeDataPlugin*>()->rootNode());
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

	QObject* obj = (QObject*)(parent.internalPointer());

	TreeData *tdata = qobject_cast<TreeData *>(obj);
	if (tdata)
	{
		int count = tdata->children().count();
		UserData* user = pluginManager->currentUser();
		QList<FileData*> files = filePlugin->filesInNodeAndUser(tdata, user);
		foreach (FileData* file, files)
		{
			if (file->mimeType() == "x-horus/x-lesson")
				count++;
		}
		return count;
	}
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

	QObject* obj = (QObject*)(parent.internalPointer());

	TreeData *tdata = qobject_cast<TreeData *>(obj);

	if (tdata)
	{
		if (row < tdata->children().count())
			return createIndex(row, column, tdata->children().at(row));
		int count = tdata->children().count();
		UserData* user = pluginManager->currentUser();
		QList<FileData*> files = filePlugin->filesInNodeAndUser(tdata, user);
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

	return createIndex(row, column, obj->children().at(row));
}

QModelIndex LessonModel::parent ( const QModelIndex & index ) const
{
    QObject* obj = (QObject*)(index.internalPointer());

    if (obj == rootItem)
        return QModelIndex();

	TreeData *tdata = qobject_cast<TreeData *>(obj);
	Lesson* lesson = qobject_cast<Lesson *>(obj);
	QObject* parent;
	if (tdata)
	{
		parent = tdata->parent();
	}
	else if (lesson)
	{
		FileData *fdata = lesson->getFiledata();
		parent = fdata->node();
	}
	else
	{
		parent = obj->parent();
	}

	if (parent == rootItem)
	{
		return createIndex(0, 0, rootItem);
	}

	TreeData *tparent = qobject_cast<TreeData *>(parent);
	Lesson* tlesson = qobject_cast<Lesson *>(parent);
	if (tparent)
	{
		return createIndex(tparent->parent()->children().indexOf(tparent), 0, parent);
	}
	else if (tlesson)
	{
		UserData* user = pluginManager->currentUser();
		FileData* fdata = tlesson->getFiledata();
		TreeData* tdata = fdata->node();
		int count = tdata->children().count();
		QList<FileData*> files = filePlugin->filesInNodeAndUser(tdata, user);
		foreach (FileData* file, files)
		{
			if (file->mimeType() == "x-horus/x-lesson")
			{
				if (file == fdata)
				{
					return createIndex(count, 0, tlesson);
				}
				count++;
			}
		}
	}

	return createIndex(parent->parent()->children().indexOf(parent), 0, parent);
}
