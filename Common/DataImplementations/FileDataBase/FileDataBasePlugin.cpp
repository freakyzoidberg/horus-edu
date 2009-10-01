#include "FileDataBasePlugin.h"
#include "FileDataBase.h"

#include "../../../Common/PluginManager.h"
#include "../../../Common/Plugin.h"
#include "../../../Common/TreeDataPlugin.h"
#include "../../../Common/UserDataPlugin.h"
#include "../../../Common/UserData.h"
#include "../../../Common/TreeData.h"

FileData* FileDataBasePlugin::getFile(quint32 fileId)
{
    if ( ! files.contains(fileId))
	{
		FileData* file = new FileDataBase(fileId, this);
#ifdef HORUS_CLIENT
		file->moveToThread(this->thread());
#endif
		files.insert(fileId, file);
	}

    return files.value(fileId);
}

QList<FileData*> FileDataBasePlugin::getFilesInNode(quint32 nodeId) const
{
	TreeData* node = pluginManager->findPlugin<TreeDataPlugin*>()->getNode(nodeId);
	return getFilesInNode(node);
}

QList<FileData*> FileDataBasePlugin::getFilesInNode(const TreeData *node) const
{
	QList<FileData*> res;
	foreach (FileData* file, files)
		if (file->node() == node)
			res.append(file);
	return res;
}

QList<FileData*> FileDataBasePlugin::getFilesInNodeAndUser(quint32 nodeId, quint32 userId) const
{
	TreeData* node = pluginManager->findPlugin<TreeDataPlugin*>()->getNode(nodeId);
	UserData* user = pluginManager->findPlugin<UserDataPlugin*>()->getUser(userId);
	QList<FileData*> res;
	return getFilesInNodeAndUser(node, user);
}

QList<FileData*> FileDataBasePlugin::getFilesInNodeAndUser(const TreeData *node, const UserData* user) const
{
	QList<FileData*> res;
	foreach (FileData* file, files)
		if (file->node() == node && file->owner() == user)
			res.append(file);
	return res;
}

FileData* FileDataBasePlugin::createNewFile(TreeData* node)
{
	static quint32 tmpId = 0;
	tmpId--;

	FileDataBase* f = ((FileDataBase*)( getFile(tmpId)) );
	f->_node = node;
	f->_owner = pluginManager->currentUser();
	return f;
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
	qDebug() << "File data Have a New Key" << file->_id;
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

		file->_node  = pluginManager->findPlugin<TreeDataPlugin*>()->getNode( query.value(4).toUInt() );
		file->_owner = pluginManager->findPlugin<UserDataPlugin*>()->getUser( query.value(5).toUInt() );

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
