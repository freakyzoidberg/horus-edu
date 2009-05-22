#ifndef TREEMANAGEMENT_H
#define TREEMANAGEMENT_H

#include <QDebug>

#include "../IServer.h"
#include "../IServerPlugin.h"

//! a Server Plugin to allow management of organisation tree
class TreeManagement : public IServerPlugin
{
  Q_OBJECT
  Q_INTERFACES(IServerPlugin)

public:
    TreeManagement();
    ~TreeManagement();

public:
    inline const QByteArray  name()    const { return "TreeManagement"; }
    inline quint8            version() const { return 1; }

    void recvPacket(quint32 userId, const PluginPacket&) const;
};


#endif // TreeManagement_H
