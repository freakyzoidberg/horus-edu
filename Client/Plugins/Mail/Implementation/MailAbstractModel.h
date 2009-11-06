#ifndef MAILABSTRACTMODEL_H
#define MAILABSTRACTMODEL_H
#include <QAbstractListModel>
#include <QStringList>
class MailAbstractModel : public QAbstractListModel
    {
        Q_OBJECT
    public:
        MailAbstractModel(const QStringList &strings, QObject *parent = 0)
            : QAbstractListModel(parent), stringList(strings) {}

        int rowCount(const QModelIndex &parent = QModelIndex()) const;
        QVariant data(const QModelIndex &index, int role) const;
        QVariant headerData(int section, Qt::Orientation orientation,
                            int role = Qt::DisplayRole) const;

    private:
        QStringList stringList;
    };

#endif
