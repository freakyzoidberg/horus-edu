#include "FileDataBase.h"
#include "FileDataBasePlugin.h"

#include "../../UserData.h"
#include "../../TreeData.h"
#include "../../PluginManager.h"
#include <QSettings>

#ifdef HORUS_CLIENT
#include <QDir>
#include <QSslSocket>
#include "../../../Client/Plugins/FileBaseClient/FileNetworkPlugin.h"
#endif
#ifdef HORUS_SERVER
#include "../../../Server/Plugins/FileBaseServer/FileNetworkPlugin.h"
#endif

FileDataBase::FileDataBase(quint32 fileId, FileDataBasePlugin* plugin) : FileData(plugin)
{
    _id = fileId;
#ifdef HORUS_CLIENT
	QFile* f = file();
	if (f->size() == _size)
		_isDownloaded = true;
	else
		_isDownloaded = false;
	delete f;
#endif
	_owner = _plugin->pluginManager->findPlugin<UserDataPlugin*>()->nobody();
	connect(_owner, SIGNAL(removed()), this, SLOT(remove()));
	_node = _plugin->pluginManager->findPlugin<TreeDataPlugin*>()->rootNode();
	connect(_node, SIGNAL(removed()), this, SLOT(remove()));
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
      << _mimeType
	  << _size
      << _hash;
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
	if (_status != CACHED && ( ! _isDownloaded || hash != _hash))
		download();
#endif
    _hash = hash;
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
	query.prepare("SELECT`name`,`mime`,`size`,`id_tree`,`id_owner`,`hash_sha1`,`mtime`FROM`file`WHERE`id`=?;");
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
	_lastChange	= query.value(5).toDateTime();

	return NONE;
}

quint8 FileDataBase::serverCreate()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("INSERT INTO`file`(`name`,`mime`,`size`,`id_tree`,`id_owner`,`hash_sha1`,`mtime`)VALUES(?,?,?,?,?,?,?);");
	query.addBindValue(_name);
	query.addBindValue(_mimeType);
	query.addBindValue(_size);
	query.addBindValue(_node->id());
	query.addBindValue(_owner->id());
	query.addBindValue(_hash.toHex());
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
	query.prepare("UPDATE`file`SET`name`=?,`mime`=?,`size`=?,`id_tree`=?,`id_owner`=?,`hash_sha1`=?,`mtime`=? WHERE`id`=?;");
    query.addBindValue(_name);
    query.addBindValue(_mimeType);
    query.addBindValue(_size);
	query.addBindValue(_node->id());
	query.addBindValue(_owner->id());
    query.addBindValue(_hash.toHex());
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

QFile* FileDataBase::file() const
{
#ifdef HORUS_SERVER
	QString dirname = QSettings().value("SETTINGS/FilesDirectory").toString();
#endif
#ifdef HORUS_CLIENT
	QString dirname = QSettings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat).value("General/TmpDir", QDir::tempPath()).toString();
#endif
	return new QFile(dirname + '/' + QVariant(_id).toString());
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
   return Data::data(column, role);
}
#endif

void FileDataBase::setName(const QString name)
{
	QMutexLocker M(&mutex);
	_name = name;
}

void FileDataBase::setMimeType(const QString type)
{
	QMutexLocker M(&mutex);
	_mimeType = type;
}

void FileDataBase::moveTo(TreeData* node)
{
	QMutexLocker M(&mutex);
	disconnect(_node, SIGNAL(removed()), this, SLOT(remove()));
	_node = node;
	connect(_node, SIGNAL(removed()), this, SLOT(remove()));
}

#ifdef HORUS_CLIENT
void FileDataBase::upload()
{
	qDebug() << "File::upload()";
	_plugin->pluginManager->findPlugin<FileNetworkPlugin*>()->askForTransfert(this, FileTransfert::UPLOAD);
}

void FileDataBase::download()
{
	qDebug() << "File::download()";
	_plugin->pluginManager->findPlugin<FileNetworkPlugin*>()->askForTransfert(this, FileTransfert::DOWNLOAD);
    _isDownloaded = false;
}

bool FileDataBase::isDownloaded() const
{
    return _isDownloaded;
}
#endif
