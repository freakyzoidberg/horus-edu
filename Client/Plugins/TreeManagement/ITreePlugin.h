#ifndef ITREEPLUGIN_H
#define ITREEPLUGIN_H

#include <QAbstractItemModel>

#include "Implementation/Tree.h"

class ITreePlugin
{
    virtual ITree* getNodeById(int id) = 0;
    virtual QAbstractItemModel* getTreeModel() = 0;
};

Q_DECLARE_INTERFACE(ITreePlugin, "net.horus.Client.TreePluginInterface/1.0");

#endif // ITREEPLUGIN_H
