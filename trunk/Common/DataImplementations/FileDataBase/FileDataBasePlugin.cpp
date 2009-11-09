#include "FileDataBasePlugin.h"
#include "FileDataBase.h"

#include "../../../Common/PluginManager.h"
#include "../../../Common/Plugin.h"
#include "../../../Common/TreeDataPlugin.h"
#include "../../../Common/UserDataPlugin.h"
#include "../../../Common/UserData.h"
#include "../../../Common/TreeData.h"

FileData* FileDataBasePlugin::file(quint32 fileId)
{
	if ( ! _files.contains(fileId))
	{
		FileData* f = new FileDataBase(fileId, this);
		f->moveToThread(this->thread());
		_files.insert(fileId, f);
	}

	return _files.value(fileId);
}

QList<FileData*> FileDataBasePlugin::filesInNode(quint32 nodeId) const
{
	TreeData* node = pluginManager->findPlugin<TreeDataPlugin*>()->node(nodeId);
	return filesInNode(node);
}

QList<FileData*> FileDataBasePlugin::filesInNode(const TreeData *node) const
{
	QList<FileData*> res;
	foreach (FileData* f, _files)
		if (f->node() == node)
			res.append(f);
	return res;
}

QList<FileData*> FileDataBasePlugin::filesInNodeAndUser(quint32 nodeId, quint32 userId) const
{
	TreeData* node = pluginManager->findPlugin<TreeDataPlugin*>()->node(nodeId);
	UserData* user = pluginManager->findPlugin<UserDataPlugin*>()->user(userId);
	QList<FileData*> res;
	return filesInNodeAndUser(node, user);
}

QList<FileData*> FileDataBasePlugin::filesInNodeAndUser(const TreeData *node, const UserData* user) const
{
	QList<FileData*> res;
	foreach (FileData* f, _files)
		if (f->node() == node && f->owner() == user)
			res.append(f);
	return res;
}

FileData* FileDataBasePlugin::createFile(TreeData* node)
{
	static quint32 tmpId = 0;
	tmpId--;

	FileDataBase* f = ((FileDataBase*)( file(tmpId)) );
	f->_node = node;
	f->_owner = pluginManager->currentUser();
	return f;
}

Data* FileDataBasePlugin::dataWithKey(QDataStream& s)
{
    quint32 tmpId;
    s >> tmpId;
	return file(tmpId);
}

QList<Data*> FileDataBasePlugin::allDatas() const
{
	QList<Data*> list;
	foreach (Data* data, _files)
		if (data->status() != Data::EMPTY)
			list.append(data);

	return list;
}
#ifdef HORUS_CLIENT
void FileDataBasePlugin::load()
{
    Plugin::load();
}

void FileDataBasePlugin::dataHaveNewKey(Data*d, QDataStream& s)
{
	FileDataBase* f = ((FileDataBase*)(d));
	_files.remove(f->_id);
	s >> f->_id;
	_files.insert(f->_id, f);
	qDebug() << "File data Have a New Key" << f->_id;
}
#endif
#ifdef HORUS_SERVER
#include "../../../Server/Plugins/FileBaseServer/FileServer.h"

void FileDataBasePlugin::load()
{
	_server = FileServer::instance();
    Plugin::load();
}

void FileDataBasePlugin::loadData()
{
	QSqlQuery query = pluginManager->sqlQuery();
	query.prepare("SELECT id,name,mime,size,id_tree,id_owner,hash_sha1,mtime FROM files;");
    query.exec();
    while (query.next())
    {
		FileDataBase* f	= (FileDataBase*)(file(query.value(0).toUInt()));
		f->_name		= query.value(1).toString();
		f->_mimeType	= query.value(2).toString();
		f->_size		= query.value(3).toUInt();

		f->_node		= pluginManager->findPlugin<TreeDataPlugin*>()->node( query.value(4).toUInt() );
		f->_owner		= pluginManager->findPlugin<UserDataPlugin*>()->user( query.value(5).toUInt() );

		f->_hash		= QByteArray::fromHex(query.value(6).toByteArray());
		f->_lastChange	= query.value(7).toDateTime();

		f->_status		= Data::UPTODATE;
    }
}

QList<Data*> FileDataBasePlugin::datasForUpdate(UserData* user, QDateTime date)
{
	QList<Data*> list;
	foreach (FileData* data, _files)
		if (data->lastChange() >= date && data->status() == Data::UPTODATE)
			list.append(data);
	return list;
}
#endif
