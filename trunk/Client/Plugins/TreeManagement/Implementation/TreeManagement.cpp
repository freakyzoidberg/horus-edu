#include "TreeManagement.h"

#include "Tree.h"

#include "../../ClientEvents.h"
#include "../../../Common/PluginPacket.h"

extern QEvent::Type ClientEvents::LoadPluginEvent;

Q_EXPORT_PLUGIN2(TreeManagement,TreeManagement)

TreeManagement::TreeManagement()
{
    qDebug() << sizeof(QObject) << sizeof(Tree) << sizeof(QByteArray) << sizeof(QString);
}

void TreeManagement::recvPacket(const PluginPacket& p)
{
//    ITree* root = Tree::getNodeById(0);
//    root->setParent(this);
//    root->dumpObjectTree();
    if (p.error)
        return;
    Tree::receiveUserTree(p.data.toList());
    for (QHash<int,Tree*>::const_iterator it = Tree::maptree.begin(); it != Tree::maptree.end(); ++it)
    {
        Tree* i = *it;
        if (i->parent())
            qDebug() << "TreeManagement::recvPacket id:" << i->getId() << "parent:" << ((ITree*)i->parent())->getId() << i->getName();
        else
            qDebug() << "TreeManagement::recvPacket id:" << i->getId() << "parent: 0 " << i->getName();
    }
}

bool TreeManagement::event(QEvent* event)
{
    qDebug() << "TreeManagement::event " << (int)event->type() << ClientEvents::LoadPluginEvent;
    if (event->type() == 65531)
    {
        qDebug() << "TreeManagement::LoadPluginEvent";
        network->sendPacket(PluginPacket("TreeManagement", "getTree+"));

//        fileManager->getFullFileList();
    }
    return false;
}
