#include "TreeDataBasePlugin.h"
#include "TreeDataBase.h"

#include "../../../Common/PluginManager.h"
#include "../../../Common/Plugin.h"

TreeDataBasePlugin::TreeDataBasePlugin()
{
}

TreeData* TreeDataBasePlugin::getNode(quint32 nodeId)
{
    if ( ! nodes.contains(nodeId))
    {
        TreeData* node = new TreeDataBase(nodeId, this);
#ifdef HORUS_CLIENT
        node->moveToThread(pluginManager->thread());
#endif
        node->setParent(0);

        nodes[nodeId] = node;
    }
    return nodes[nodeId];
}

Data* TreeDataBasePlugin::getDataWithKey(QDataStream& s)
{
    quint32 tmpId;
    s >> tmpId;
    return getNode(tmpId);
}

#ifdef HORUS_CLIENT
void TreeDataBasePlugin::dataHaveNewKey(Data*d, QDataStream& s)
{
    quint32 tmpId;
    s >> tmpId;
    ((TreeDataBase*)(d))->nodeId = tmpId;
}

#include "../../../Client/Plugins/TreeBaseClient/TreeModel.h"

QAbstractItemModel* TreeDataBasePlugin::getTreeModel()
{
    return new TreeModel(pluginManager);
}
#endif
#ifdef HORUS_SERVER
bool TreeDataBasePlugin::verifyDataBase(QSqlQuery& TODO)
{
    return true;
}
#endif
