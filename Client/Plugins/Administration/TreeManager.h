#ifndef TREEMANAGER_H
#define TREEMANAGER_H

#include <QObject>
#include <QHash>
#include <QVariant>

class TreeManager : public QObject
{
    public:
        TreeManager();
        QVariantHash    getTree();
        QVariantHash    getNodInfo();
        void            deleteNode(QString idNode);
        void            moveNode(QString from, QString to);
        void            editNode(QString id, QString type, QString name, QString userId);
};

#endif // TREEMANAGER_H
