#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QMultiHash>
#include <QtGui/QIcon>
#include <QAbstractItemModel>

class TreeModel : public QAbstractItemModel
{
public:
    TreeModel();

    int         columnCount ( const QModelIndex & parent = QModelIndex() ) const;
    int         rowCount ( const QModelIndex & parent = QModelIndex() ) const;
//    QVariant    headerData ( int section, Qt::Orientation orientation, int role) const;
    QVariant    data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const;
    QModelIndex parent ( const QModelIndex & index ) const;

private:
    static QIcon    LessonIcon;
    static QIcon    GradeIcon;
    static QIcon    SubjectIcon;
    static QIcon    FileIcon;
    static QIcon    GroupIcon;
    static QIcon    RootIcon;
    static QIcon    DefaultIcon;
};

#endif // TREEMODEL_H
