#ifndef TREEDATAPLUGIN_H
#define TREEDATAPLUGIN_H

#ifdef HORUS_CLIENT
    #include <QAbstractItemModel>
#endif

#include "DataPlugin.h"

class TreeData;
class TreeDataPlugin : public DataPlugin
{
    Q_OBJECT
#ifdef HORUS_SERVER
    Q_INTERFACES(ServerDataPlugin)
#endif
#ifdef HORUS_CLIENT
    Q_INTERFACES(ClientDataPlugin)
#endif

public:
    virtual TreeData* getNode(quint32 id) = 0;
#ifdef HORUS_CLIENT
    virtual QAbstractItemModel* getTreeModel() = 0;
#endif
};

#ifdef HORUS_SERVER
typedef TreeDataPlugin ServerTreeDataPlugin;
Q_DECLARE_INTERFACE(ServerTreeDataPlugin, "net.horus.ServerTreeDataPlugin/1.0");
#endif
#ifdef HORUS_CLIENT
typedef TreeDataPlugin ClientTreeDataPlugin;
Q_DECLARE_INTERFACE(ClientTreeDataPlugin, "net.horus.ClientTreeDataPlugin/1.0");
#endif

#endif // TREEDATAPLUGIN_H
