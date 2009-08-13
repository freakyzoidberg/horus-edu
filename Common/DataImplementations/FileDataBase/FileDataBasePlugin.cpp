#include "FileDataBasePlugin.h"
#include "FileDataBase.h"

#include "../../../Common/PluginManager.h"
#include "../../../Common/Plugin.h"

FileDataBasePlugin::FileDataBasePlugin()
{
}

FileData* FileDataBasePlugin::getNode(quint32 nodeId)
{
    if ( ! nodes.contains(nodeId))
    {
        nodes[nodeId] = new FileDataBase(nodeId, this);
        nodes[nodeId]->setParent(0);
    }
    return nodes[nodeId];
}

Data* FileDataBasePlugin::getDataWithKey(QDataStream& s)
{
    quint32 tmpId;
    s >> tmpId;
    return getNode(tmpId);
}

#ifdef HORUS_CLIENT
void FileDataBasePlugin::dataHaveNewKey(Data*d, QDataStream& s)
{
    quint32 tmpId;
    s >> tmpId;
    ((FileDataBase*)(d))->nodeId = tmpId;
}
#endif
#ifdef HORUS_SERVER
bool FileDataBasePlugin::verifyDataBase(QSqlQuery& TODO)
{
    return true;
}
#endif
