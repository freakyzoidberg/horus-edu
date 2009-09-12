#ifndef LESSONMODEL_H
#define LESSONMODEL_H

#include <QAbstractItemModel>
#include "../../../Common/TreeData.h"
#include "../../../Common/PluginManager.h"

class LessonModel : public QAbstractItemModel
{
public:
    LessonModel(PluginManager* pluginManager);
    int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
    int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const;
    QModelIndex parent ( const QModelIndex & index ) const;

private:
    PluginManager*  pluginManager;
    Data*           rootItem;
};

#endif // LESSONMODEL_H