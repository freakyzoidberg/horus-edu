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
#include "FileDataBase.h"
#include "FileDataBasePlugin.h"

#include "../../UserData.h"
#include "../../TreeData.h"
#include "../../PluginManager.h"
#include <QSettings>
#include <QDir>

#ifdef HORUS_CLIENT
#include <QSslSocket>
#include "../../../Client/Plugins/FileBaseClient/FileNetworkPlugin.h"
#endif
#ifdef HORUS_SERVER
#include "../../../Server/Plugins/FileBaseServer/FileNetworkPlugin.h"
#endif

FileDataBase::FileDataBase(quint32 fileId, FileDataBasePlugin* plugin) : FileData(plugin)
{
    _id = fileId;
	_mimeType = "unknow";
#ifdef HORUS_CLIENT
	_isDownloaded = false;
#endif
	_owner = _plugin->pluginManager->currentUser();
	if ( ! _owner)
		_owner = _plugin->pluginManager->nobody();
	connect(_owner, SIGNAL(removed()), this, SLOT(remove()));
	_node = _plugin->pluginManager->findPlugin<TreeDataPlugin*>()->rootNode();
	connect(_node, SIGNAL(removed()), this, SLOT(remove()));
	_size = 0;
	_mimeType = "application/octet-stream";
}

void FileDataBase::keyToStream(QDataStream& s) const
{
    s << _id;
}

void FileDataBase::dataToStream(QDataStream& s) const
{
    s << _id
      << _name
	  << _owner->id()
	  << _node->id()
	  << _keyWords
      << _mimeType
	  << _size
      << _hash;
	Data::dataToStream(s);
}

void FileDataBase::dataFromStream(QDataStream& s)
{
    quint32 ownerId;
    quint32 nodeId;
    QByteArray hash;

    s >> _id
      >> _name
      >> ownerId
      >> nodeId
	  >> _keyWords
      >> _mimeType
	  >> _size
      >> hash;

	disconnect(_owner, SIGNAL(removed()), this, SLOT(remove()));
	_owner = _plugin->pluginManager->findPlugin<UserDataPlugin*>()->user(ownerId);
	connect(_owner, SIGNAL(removed()), this, SLOT(remove()));
	disconnect(_node, SIGNAL(removed()), this, SLOT(remove()));
	_node = _plugin->pluginManager->findPlugin<TreeDataPlugin*>()->node(nodeId);
	connect(_node, SIGNAL(removed()), this, SLOT(remove()));
#ifdef HORUS_CLIENT
	//auto download
	QFile f(fileName());
	if (f.size() != (qint64)_size && ( ! _isDownloaded || hash != _hash))
		download();
#endif
    _hash = hash;
	Data::dataFromStream(s);
}

bool FileDataBase::canChange(UserData* user) const
{
	if (user->level() <= LEVEL_ADMINISTRATOR || user == _owner)
		return true;
	return _node->canChange(user);
}

bool FileDataBase::canAccess(UserData* user) const
{
	if (user->level() <= LEVEL_ADMINISTRATOR || user == _owner)
		return true;
	return _node->canAccess(user);
}

QDebug FileDataBase::operator<<(QDebug debug) const
{
    return debug
      << _id
	  << _name;
}

const QList<Data*> FileDataBase::dependsOfCreatedData() const
{
	QList<Data*> list;
	list.append(_owner);
	list.append(_node);
	return list;
}

#ifdef HORUS_SERVER
quint8 FileDataBase::serverRead()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("SELECT`name`,`mime`,`size`,`id_tree`,`id_owner`,`hash_sha1`,`keywords`,`mtime`FROM`file`WHERE`id`=?;");
	query.addBindValue(_id);

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
	if ( ! query.next())
		return NOT_FOUND;

	_name		= query.value(0).toString();
	_mimeType	= query.value(1).toString();
	_size		= query.value(2).toUInt();
	_node		= _plugin->pluginManager->findPlugin<TreeDataPlugin*>()->node( query.value(3).toUInt() );
	_owner		= _plugin->pluginManager->findPlugin<UserDataPlugin*>()->user( query.value(4).toUInt() );
	_hash		= query.value(5).toByteArray();
	_keyWords	= query.value(6).toString();
	_lastChange	= query.value(7).toDateTime();

	return NONE;
}

quint8 FileDataBase::serverCreate()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("INSERT INTO`file`(`name`,`mime`,`size`,`id_tree`,`id_owner`,`hash_sha1`,`keywords`,`mtime`)VALUES(?,?,?,?,?,?,?,?);");
	query.addBindValue(_name);
	query.addBindValue(_mimeType);
	query.addBindValue(_size);
	query.addBindValue(_node->id());
	query.addBindValue(_owner->id());
	query.addBindValue(_hash.toHex());
	query.addBindValue(_keyWords);
	query.addBindValue( (_lastChange = QDateTime::currentDateTime()) );

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}

	_id = query.lastInsertId().toUInt();

	return NONE;
}

quint8 FileDataBase::serverSave()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("UPDATE`file`SET`name`=?,`mime`=?,`size`=?,`id_tree`=?,`id_owner`=?,`hash_sha1`=?,`keywords`=?,`mtime`=? WHERE`id`=?;");
    query.addBindValue(_name);
    query.addBindValue(_mimeType);
    query.addBindValue(_size);
	query.addBindValue(_node->id());
	query.addBindValue(_owner->id());
    query.addBindValue(_hash.toHex());
	query.addBindValue(_keyWords);
	query.addBindValue( (_lastChange = QDateTime::currentDateTime()) );
	query.addBindValue(_id);

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
	return NONE;
}

quint8 FileDataBase::serverRemove()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("DELETE FROM`file`WHERE`id`=?;");
	query.addBindValue(_id);

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
	if ( ! query.numRowsAffected())
		return NOT_FOUND;

	return NONE;
}
#endif

QString FileDataBase::fileName() const
{
#ifdef HORUS_SERVER
	QString pathSys(QSettings().value("SETTINGS/FilesDirectory", QDir::tempPath()).toString());
#endif
#ifdef HORUS_CLIENT
	QString pathSys(QSettings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat).value("General/TmpDir", QDir::tempPath()).toString());
#endif

	QString pathFile = "/";
	for (TreeData* node = _node; node; node = node->parent())
		pathFile = '/' + node->name() + pathFile;

	QDir().mkpath(pathSys + pathFile);

	return pathSys + pathFile + _name;
}

#ifdef HORUS_CLIENT
#include <QIcon>
QVariant FileDataBase::data(int column, int role) const
{
    if (role == Qt::DisplayRole)
    {
		if (column == -1)
            return _id;
		if (column == 0)
            return _name;
		if (column == 1)
            return _mimeType;
		if (column == 2)
            return _owner->id();
		if (column == 3)
            return _node->id();
    }
    else if (role == Qt::DecorationRole && column == 0)
	{
		QString icon = ":/Icons/" + QString(_mimeType).replace('/', '-') + ".png";

		if (QFile::exists(icon))
			return QIcon(icon);

		return QIcon(":/Icons/x-generic.png");
    }
	else if (role == FILTER_ROLE)
	{
		if (column == 0)
			return _name + _keyWords;
	}
   return Data::data(column, role);
}
#endif

void FileDataBase::setName(const QString name)
{
	if (_name != name)
	{
		QMutexLocker M(&mutex);
		QString oldName = fileName();
		_name = name;
		QString newName = fileName();
		QFile::rename(oldName, newName);
	}
}

void FileDataBase::setMimeType(const QString type)
{
	QMutexLocker M(&mutex);
	_mimeType = type;
}

void FileDataBase::setKeyWords(QString keyWords)
{
	QMutexLocker M(&mutex);
	_keyWords = keyWords;
}

void FileDataBase::moveTo(TreeData* node)
{
	QMutexLocker M(&mutex);
	disconnect(_node, SIGNAL(removed()), this, SLOT(remove()));
	_node = node;
	connect(_node, SIGNAL(removed()), this, SLOT(remove()));
}

#ifdef HORUS_CLIENT
void FileDataBase::upload(const QString localFileName)
{
	if (QFileInfo(localFileName).size() == QFileInfo(fileName()).size())
	{
		qDebug() << this << "Already uploaded.";
		return;
	}
	QFile::copy(localFileName, fileName());

	if (_status == EMPTY || _status == CREATING)
		connect(this, SIGNAL(updated()), this, SLOT(upload()));
	else
		upload();
}

void FileDataBase::upload()
{
	disconnect(this, SIGNAL(updated()), this, SLOT(upload()));
	_plugin->pluginManager->findPlugin<FileNetworkPlugin*>()->askForTransfert(this, FileTransfert::UPLOAD);
}

void FileDataBase::download()
{
	qDebug() << this << "download";
	if ( ! _isDownloaded)
	{
		QFile f(fileName());
		if (f.size() == (qint64)_size)
			_isDownloaded = true;
	}

	if (_isDownloaded)
	{
		qDebug() << this << "Already downloaded." ;
		return;
	}

	_plugin->pluginManager->findPlugin<FileNetworkPlugin*>()->askForTransfert(this, FileTransfert::DOWNLOAD);
    _isDownloaded = false;
}

bool FileDataBase::isDownloaded() const
{
    return _isDownloaded;
}
#endif
