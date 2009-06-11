#include "TreeManagement.h"

#include "Tree.h"

#include "../../ClientEvents.h"
#include "../../../Common/PluginPacket.h"

extern QEvent::Type ClientEvents::LoadPluginEvent;

Q_EXPORT_PLUGIN2(TreeManagement,TreeManagement)

TreeManagement::TreeManagement()
{
}

void TreeManagement::recvPacket(const PluginPacket& p)
{
//    qDebug() << p.data;
    if (p.error)
        return;
    Tree::receiveUserTree(p.data.toList());
    for (QHash<int,Tree*>::const_iterator it = Tree::maptree.begin(); it != Tree::maptree.end(); ++it)
    {
        Tree* i = *it;
        qDebug() << "TreeManagement::recvPacket id:" << i->getId() << "parent:" << ((ITree*)i->parent())->getId() << i->getName();
    }
}

bool TreeManagement::event(QEvent* event)
{
    qDebug() << "TreeManagement::event " << (int)event->type() << ClientEvents::LoadPluginEvent;
//    if (event->type() == ClientEvents::LoadPluginEvent)
    {
//        qDebug() << "TreeManagement::LoadPluginEvent";
        network->sendPacket(PluginPacket("TreeManagement", "getTree+"));

//        fileManager->getFullFileList();
    }
    return false;
}
