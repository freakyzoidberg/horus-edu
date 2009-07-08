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
        nodes[nodeId] = new TreeDataBase(nodeId, this);

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

#include "TreeModel.h"

QAbstractItemModel* TreeDataBasePlugin::getTreeModel()
{
    return new TreeModel();
}
#endif
#ifdef HORUS_SERVER
bool TreeDataBasePlugin::verifyDataBase(QSqlQuery& TODO)
{
    return true;
}
#endif
