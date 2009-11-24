#include "FileDataBasePlugin.h"
#include "FileDataBase.h"

#include "../../../Common/PluginManager.h"
#include "../../../Common/Plugin.h"
#include "../../../Common/TreeDataPlugin.h"
#include "../../../Common/UserDataPlugin.h"
#include "../../../Common/UserData.h"
#include "../../../Common/TreeData.h"
#ifdef HORUS_SERVER
#include "../../../Server/Plugins/FileBaseServer/FileServer.h"
#endif

FileDataBasePlugin::FileDataBasePlugin()
{
}

FileData* FileDataBasePlugin::file(quint32 fileId)
{
	foreach (Data* d, _allDatas)
	{
		FileDataBase* f = (FileDataBase*)d;
		if (f->_id == fileId)
			return f;
	}

	FileData* f = new FileDataBase(fileId, this);
	f->moveToThread(thread());
	_allDatas.append(f);
	return f;
}

QList<FileData*> FileDataBasePlugin::filesInNode(const TreeData *node) const
{
	QList<FileData*> res;
	foreach (Data* d, _allDatas)
	{
		FileDataBase* f = (FileDataBase*)d;
		if (f->_node == node)
			res.append(f);
	}
	return res;
}

QList<FileData*> FileDataBasePlugin::filesInNodeAndUser(const TreeData *node, const UserData* user) const
{
	QList<FileData*> res;
	foreach (Data* d, _allDatas)
	{
		FileDataBase* f = (FileDataBase*)d;
		if (f->node() == node && f->owner() == user)
			res.append(f);
	}
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
#ifdef HORUS_CLIENT
void FileDataBasePlugin::dataHaveNewKey(Data*d, QDataStream& s)
{
	FileDataBase* f = ((FileDataBase*)(d));
	s >> f->_id;
	qDebug() << "File data Have a New Key" << f->_id;
}

#include "../../../Client/DataListModel.cpp"
QAbstractListModel* FileDataBasePlugin::listModel() const
{
	static DataListModel* _model = new DataListModel(this);
	return _model;
}
#endif
void FileDataBasePlugin::load()
{
#ifdef HORUS_SERVER
	_server = FileServer::instance();

	QSqlQuery query = pluginManager->sqlQuery();
	query.prepare("SELECT`id`,`name`,`mime`,`size`,`id_tree`,`id_owner`,`hash_sha1`,`mtime`FROM`file`;");
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
#endif
	Plugin::load();
}

void FileDataBasePlugin::unload()
{
	foreach (Data* d, _allDatas)
		delete (FileDataBase*)d;
	_allDatas.clear();
	DataPlugin::unload();
}

bool FileDataBasePlugin::canLoad() const
{
	TreeDataPlugin* tree = pluginManager->findPlugin<TreeDataPlugin*>();
	UserDataPlugin* user = pluginManager->findPlugin<UserDataPlugin*>();
	if ( ! tree || ! tree->canLoad() || ! user || ! user->canLoad())
		return false;

#ifdef HORUS_SERVER
	QSqlQuery query = pluginManager->sqlQuery();
	if ( ! query.exec("CREATE TABLE IF NOT EXISTS`file` (\
						`id` int(11) NOT NULL auto_increment,\
						`name` varchar(255) NOT NULL,\
						`mime` varchar(64) NOT NULL,\
						`size` int(11) NOT NULL,\
						`id_tree` int(11) NOT NULL,\
						`id_owner` int(11) NOT NULL,\
						`hash_sha1` varchar(40) NOT NULL,\
						`mtime` timestamp NOT NULL,\
						PRIMARY KEY (`id`),\
						KEY`id_owner`(`id_owner`),\
						KEY`id_tree`(`id_tree`)\
					);")
		||
		 ! query.exec("SELECT`id`,`name`,`mime`,`size`,`id_tree`,`id_owner`,`hash_sha1`,`mtime`FROM`file`WHERE`id`=-1;")
		)
	{
		qDebug() << "FileDataBasePlugin::canLoad()" << query.lastError();
		return false;
	}
#endif
	return DataPlugin::canLoad();
}
