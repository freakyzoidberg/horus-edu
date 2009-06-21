#ifndef TREEDATAPLUGIN_H
#define TREEDATAPLUGIN_H

#include <QAbstractItemModel>

#include "TreeData.h"

class TreeDataPlugin : public DataPlugin
{
public:
    virtual TreeData* getNodeById(quint32 id) = 0;
    virtual QAbstractItemModel* getTreeModel() = 0;
};

Q_DECLARE_INTERFACE(TreeDataPlugin, "net.horus.Client.TreeDataPlugin/1.0");

#endif // TREEDATAPLUGIN_H
