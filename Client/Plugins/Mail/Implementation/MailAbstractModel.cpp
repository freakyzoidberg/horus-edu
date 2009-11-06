#include "MailAbstractModel.h"
#include <QMap>
#include <QDebug>

MailAbstractModel::MailAbstractModel() {
}

int MailAbstractModel::rowCount(const QModelIndex & ) const {
    return row;
}

void MailAbstractModel::setRow(int siz)
{
    row = siz;
}

int MailAbstractModel::columnCount(const QModelIndex & ) const {
    return 4;
}

void MailAbstractModel::RefreshList(){
    reset();
}

QVariant MailAbstractModel::data(const QModelIndex &index, int role) const {
    if(!index.isValid())
    {

        return QVariant();
    }
    if (role == Qt::BackgroundColorRole) {
        //return (QVariant) ( QColor( Qt::yellow ) );
    }

    if (role == Qt::FontRole) {
        if(index.column() == 0) {
         QFont font;
         font.setBold(true);
         return font;
        }
    }

    if (role == Qt::TextAlignmentRole) {
        if(index.column() == 0) {
           return (QVariant) ( Qt::AlignRight | Qt::AlignVCenter );
        } else {
           return (QVariant) ( Qt::AlignLeft | Qt::AlignVCenter );
        }
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole) {

        return mydata[index.row()][index.column()];
        //return QVariant("Cell text");
    }

   return QVariant();
}

bool MailAbstractModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() && role == Qt::EditRole)
    {
        // we have index.row() index.column() and value
            // all we need
        QMap<int, QVariant> temp = mydata[index.row()];
        temp.insert(index.column(), value);
        mydata.insert(index.row(), temp);

        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags MailAbstractModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) return Qt::ItemIsEnabled;
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
    // return QAbstractItemModel::flags(index);
}

QVariant MailAbstractModel::headerData(int section, Qt::Orientation orientation, int role) const  {
    if (role != Qt::DisplayRole) return QVariant();
    if (orientation == Qt::Horizontal) {
        if (section == 1)
            return "Date";
        else if (section == 0)
            return "#";
        else if (section == 2)
            return "From";
        else if (section == 3)
            return "Subject";
        else
            return "Header";
    } else {

        return "Row";
    }
    return "";
}



