#ifndef WHITEBOARDMODEL_H
#define WHITEBOARDMODEL_H

#include <QMultiHash>
#include <QtGui/QIcon>
#include <QAbstractItemModel>

class PluginManager;
class Data;
class WhiteBoardModel : public QAbstractItemModel
{
	Q_OBJECT
public:
    WhiteBoardModel(PluginManager* pluginManager);

    int         columnCount ( const QModelIndex & parent = QModelIndex() ) const;
    int         rowCount ( const QModelIndex & parent = QModelIndex() ) const;
//    QVariant    headerData ( int section, Qt::Orientation orientation, int role) const;
    QVariant    data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const;
    QModelIndex parent ( const QModelIndex & index ) const;

private:
    PluginManager*  pluginManager;
    Data*           rootItem;
};

#endif // WHITEBOARDMODEL_H
