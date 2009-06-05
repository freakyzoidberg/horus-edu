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
    qDebug() << "toto";
    Tree::receiveUserTree(p.data.toHash());
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
    }
    return false;
}
