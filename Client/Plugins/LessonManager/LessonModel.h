#ifndef LESSONMODEL_H
#define LESSONMODEL_H

#include <QAbstractItemModel>
#include "../../../Common/TreeData.h"
#include "../../../Common/PluginManager.h"
#include "../../../Common/FileDataPlugin.h"
#include "ILesson.h"
#include "ILessonDocument.h"

class LessonModel : public QAbstractItemModel
{
public:
    LessonModel(PluginManager* pluginManager);
    int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
    int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
	QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const;
    QModelIndex parent ( const QModelIndex & index ) const;
        Qt::ItemFlags flags( const QModelIndex & index) const;
	QStringList mimeTypes() const;
	QMimeData *mimeData(const QModelIndexList &indexes) const;
	virtual bool createLesson(QModelIndex&) = 0;
	virtual ILesson* getLesson(int id) = 0;
	virtual ILessonDocument* getLessonDocument(int lessonId, int documentId) = 0;

protected:
    PluginManager*  pluginManager;
	FileDataPlugin*		filePlugin;
    Data*           rootItem;
};

#endif // LESSONMODEL_H
