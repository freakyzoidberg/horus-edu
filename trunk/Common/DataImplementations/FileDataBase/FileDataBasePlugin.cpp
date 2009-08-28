#include "FileDataBasePlugin.h"
#include "FileDataBase.h"

#include "../../../Common/PluginManager.h"
#include "../../../Common/Plugin.h"

FileData* FileDataBasePlugin::getFile(quint32 fileId)
{
    if ( ! files.contains(fileId))
        files.insert(fileId, new FileDataBase(fileId, this));

    return files.value(fileId);
}

FileData* FileDataBasePlugin::getFile(quint32 nodeId, QString fileName)
{
    //TODO
    return 0;
}

Data* FileDataBasePlugin::getDataWithKey(QDataStream& s)
{
    quint32 tmpId;
    s >> tmpId;
    return getFile(tmpId);
}

#ifdef HORUS_CLIENT
void FileDataBasePlugin::load()
{
    Plugin::load();
}

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
