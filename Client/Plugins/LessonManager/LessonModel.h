#ifndef LESSONMODEL_H
#define LESSONMODEL_H

#include <QAbstractItemModel>
#include "../../../Common/TreeData.h"
#include "../../../Common/PluginManager.h"
#include "../../../Common/FileDataPlugin.h"

//#ifndef TEST_METADATA
//# define TEST_METADATA
//#endif

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
private:
    PluginManager*  pluginManager;
	FileDataPlugin*		filePlugin;
#ifdef TEST_METADATA
    QObject*        rootItem;
#else
    Data*           rootItem;
#endif
};

#endif // LESSONMODEL_H
