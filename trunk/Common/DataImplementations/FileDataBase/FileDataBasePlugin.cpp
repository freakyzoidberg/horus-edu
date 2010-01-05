/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "FileDataBasePlugin.h"
#include "FileDataBase.h"

#include <QFileInfo>
#include "../../../Common/PluginManager.h"
#include "../../../Common/Plugin.h"
#include "../../../Common/TreeDataPlugin.h"
#include "../../../Common/UserDataPlugin.h"
#include "../../../Common/UserData.h"
#include "../../../Common/TreeData.h"
#ifdef HORUS_SERVER
#include "../../../Server/Plugins/FileBaseServer/FileServer.h"
#endif
#ifdef HORUS_CLIENT
#include "../../../Client/DataListModel.h"
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

FileData* FileDataBasePlugin::createFile()
{
	static quint32 tmpId = 0;
	tmpId--;
	return static_cast<FileDataBase*>( file(tmpId));
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
	FileDataBase* f = static_cast<FileDataBase*>(d);
	s >> f->_id;
	qDebug() << "File data Have a New Key" << f->_id;
}
#endif
void FileDataBasePlugin::load()
{
#ifdef HORUS_SERVER
	_server = FileServer::instance();

	QSqlQuery query = pluginManager->sqlQuery();
	query.prepare("SELECT`id`,`name`,`mime`,`size`,`id_tree`,`id_owner`,`hash_sha1`,`keywords`,`mtime`FROM`file`;");
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
		f->_keyWords	= query.value(7).toString();
		f->_lastChange	= query.value(8).toDateTime();

		f->_status		= Data::UPTODATE;
	}
#endif
#ifdef HORUS_CLIENT
	_model = new DataListModel(this);
#endif
	Plugin::load();
}

void FileDataBasePlugin::unload()
{
	foreach (Data* d, _allDatas)
		delete (FileDataBase*)d;
	_allDatas.clear();
#ifdef HORUS_CLIENT
	delete _model;
#endif
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
						`keywords` varchar(255) NOT NULL,\
						PRIMARY KEY (`id`),\
						KEY`id_owner`(`id_owner`),\
						KEY`id_tree`(`id_tree`)\
					);")
		||
		 ! query.exec("SELECT`id`,`name`,`mime`,`size`,`id_tree`,`id_owner`,`hash_sha1`,`keywords`,`mtime`FROM`file`WHERE`id`=-1;")
		)
	{
		qDebug() << "FileDataBasePlugin::canLoad()" << query.lastError();
		return false;
	}
#endif
	return DataPlugin::canLoad();
}
