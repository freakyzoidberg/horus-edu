#include "FileDataBasePlugin.h"
#include "FileDataBase.h"

#include "../../../Common/PluginManager.h"
#include "../../../Common/Plugin.h"
#include "../../../Common/TreeDataPlugin.h"
#include "../../../Common/UserDataPlugin.h"

FileData* FileDataBasePlugin::getFile(quint32 fileId)
{
    if ( ! files.contains(fileId))
        files.insert(fileId, new FileDataBase(fileId, this));

    return files.value(fileId);
}

Data* FileDataBasePlugin::getDataWithKey(QDataStream& s)
{
    quint32 tmpId;
    s >> tmpId;
    return getFile(tmpId);
}

Data* FileDataBasePlugin::getNewData()
{
    static quint32 uniqueId = 0;
    return getFile(--uniqueId);
}

#ifdef HORUS_CLIENT
void FileDataBasePlugin::load()
{
    Plugin::load();
}

void FileDataBasePlugin::dataHaveNewKey(Data*d, QDataStream& s)
{
    FileDataBase* file = ((FileDataBase*)(d));

    files.remove(file->_id);

    s >> file->_id;
    files.insert(file->_id, file);
}
#endif
#ifdef HORUS_SERVER
#include "../../../Server/Plugins/FileBaseServer/FileServer.h"

void FileDataBasePlugin::load()
{
    server = FileServer::instance();
    Plugin::load();
}

void FileDataBasePlugin::loadDataBase(QSqlQuery& query)
{
    query.prepare("SELECT id,name,mime,size,id_tree,id_owner,hash_sha1,mtime FROM files;");
    query.exec();
    while (query.next())
    {
        FileDataBase* file = (FileDataBase*)(getFile(query.value(0).toUInt()));
        file->_name        = query.value(1).toString();
        file->_mimeType    = query.value(2).toString();
        file->_size        = query.value(3).toUInt();

        TreeDataPlugin* treePlugin = pluginManager->findPlugin<TreeDataPlugin*>();
        if (treePlugin)
            file->_node    = treePlugin->getNode( query.value(4).toUInt() );
        else
            file->_node    = 0;

        UserDataPlugin* userPlugin = pluginManager->findPlugin<UserDataPlugin*>();
        if (userPlugin)
            file->_owner   = userPlugin->getUser( query.value(5).toUInt() );
        else
            file->_owner   = 0;

        file->_hash        = QByteArray::fromHex(query.value(6).toByteArray());
        file->_lastChange  = query.value(7).toDateTime();

        file->_status = Data::UPTODATE;
    }
}

void FileDataBasePlugin::sendUpdates(QSqlQuery&, UserData* user, QDateTime date)
{
    foreach (FileData* file, files)
        if (file->lastChange() >= date)
            dataManager->sendData(user, file);
}
#endif