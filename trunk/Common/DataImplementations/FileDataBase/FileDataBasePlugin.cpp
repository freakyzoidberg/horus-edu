#include "FileDataBasePlugin.h"
#include "FileDataBase.h"

#include "../../../Common/PluginManager.h"
#include "../../../Common/Plugin.h"

FileData* FileDataBasePlugin::getFile(quint32 fileId)
{
    return 0;
}

FileData* FileDataBasePlugin::getFile(quint32 nodeId, QString fileName)
{
    return 0;
}

Data* FileDataBasePlugin::getDataWithKey(QDataStream& s)
{
    quint32 tmpId;
    s >> tmpId;
    return getFile(tmpId);
}

#ifdef HORUS_CLIENT
void FileDataBasePlugin::dataHaveNewKey(Data*d, QDataStream& s)
{
    quint32 tmpId;
    s >> tmpId;
    ((FileDataBase*)(d))->id = tmpId;
}
#endif
#ifdef HORUS_SERVER
#include "../../../Server/Plugins/FileBaseServer/FileServer.h"

void FileDataBasePlugin::load()
{
    server = new FileServer;
    Plugin::load();
}

bool FileDataBasePlugin::verifyDataBase(QSqlQuery& TODO)
{
    return true;
}
#endif
