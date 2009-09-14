#ifndef STUDENTMODEL_H
#define STUDENTMODEL_H


#include <QAbstractItemModel>
 #include <QModelIndex>
 #include <QVariant>

class StudentModel: public QAbstractItemModel
{
    Q_OBJECT

    public:
     StudentModel(const QString &data, QObject *parent = 0);
     ~StudentModel();

     QVariant data(const QModelIndex &index, int role) const;
     Qt::ItemFlags flags(const QModelIndex &index) const;
     QVariant headerData(int section, Qt::Orientation orientation,
                         int role = Qt::DisplayRole) const;
     QModelIndex index(int row, int column,
                       const QModelIndex &parent = QModelIndex()) const;
     QModelIndex parent(const QModelIndex &index) const;
     int rowCount(const QModelIndex &parent = QModelIndex()) const;
     int columnCount(const QModelIndex &parent = QModelIndex()) const;

 private:
     void setupModelData(const QStringList &lines);

};

#endif // STUDENTMODEL_H
