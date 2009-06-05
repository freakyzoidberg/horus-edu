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
    Tree::receiveUserTree(p.data.toHash());
    for (QHash<int,Tree*>::const_iterator it = Tree::maptree.begin(); it != Tree::maptree.end(); ++it)
    {
        Tree* i = *it;
        qDebug() << "TreeManagement::recvPacket NODE:" << i->Getid() << i << i->GetParent()->Getid() << i->GetParent() << i->GetSonsNode() << i->GetName();
    }
}

bool TreeManagement::event(QEvent* event)
{
    qDebug() << "TreeManagement::event " << (int)event->type() << ClientEvents::LoadPluginEvent;
//    if (event->type() == ClientEvents::LoadPluginEvent)
    {
//        qDebug() << "TreeManagement::LoadPluginEvent";
        QVariantHash request;
        request["Request"] = "getTree+";
        network->sendPacket(PluginPacket("TreeManagement", request));

        fileManager->getFullFileList();
    }
    return false;
}
