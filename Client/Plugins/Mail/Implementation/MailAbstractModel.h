#ifndef MAILABSTRACTMODEL_H
#define MAILABSTRACTMODEL_H
#include <QAbstractListModel>
#include <QStringList>
#include <QMap>
#include <QFont>
class MailAbstractModel : public QAbstractTableModel
    {
     Q_OBJECT
    public:
        MailAbstractModel();
        int rowCount(const QModelIndex &parent = QModelIndex()) const;
        int columnCount(const QModelIndex & ) const;
        QVariant headerData(int section, Qt::Orientation orientation, int role) const;
        QVariant data(const QModelIndex &index, int role) const;
        Qt::ItemFlags flags(const QModelIndex &index) const;
        bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
        void RefreshList();
        void setRow(int siz);
     private:
        int row;
        QMap<int, QMap<int, QVariant> > mydata;

    };

#endif
