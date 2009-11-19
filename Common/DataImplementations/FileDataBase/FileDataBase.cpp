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
	_name = "Empty";
	_hash = "";
	_mimeType = "";
	_owner = 0;
	_node = 0;
    QSettings settings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat);
#endif
}
void FileDataBase::keyToStream(QDataStream& s)
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

	_owner = _plugin->pluginManager->findPlugin<UserDataPlugin*>()->user(ownerId);
	_node = _plugin->pluginManager->findPlugin<TreeDataPlugin*>()->node(nodeId);
#ifdef HORUS_CLIENT
	//auto download
	if (_status != CACHED && ( ! _isDownloaded || hash != _hash))
		download();
#endif
    _hash = hash;
}

QDebug FileDataBase::operator<<(QDebug debug) const
{
    return debug
      << _id
	  << _name;
	  //<< _owner->id()
	  //<< _node->id()
	  //<< _mimeType;
}

#ifdef HORUS_SERVER
quint8 FileDataBase::serverRead()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("SELECT name,mime,size,id_tree,id_owner,hash_sha1,mtime FROM files WHERE id=?;");
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
	query.prepare("INSERT INTO files (name,mime,size,id_tree,id_owner,hash_sha1,mtime) VALUES (?,?,?,?,?,?,?);");
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

	((FileDataBasePlugin*)_plugin)->_files.remove(_id);
	_id = query.lastInsertId().toUInt();
	((FileDataBasePlugin*)_plugin)->_files.insert(_id, this);

	return NONE;
}

quint8 FileDataBase::serverSave()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("UPDATE files SET name=?,mime=?,size=?,id_tree=?,id_owner=?,hash_sha1=?,mtime=? WHERE id=?;");
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
	if ( ! query.numRowsAffected())
		return NOT_FOUND;

	return NONE;
}

quint8 FileDataBase::serverRemove()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("DELETE FROM File WHERE id=?;");
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
    if (_name == name)
        return;

    _name = name;
}

void FileDataBase::setMimeType(const QString type)
{
	if (_mimeType == type)
		return;

	_mimeType = type;
}

void FileDataBase::moveTo(TreeData* node)
{
    if ( ! node || _node == node)
        return;

    _node = node;
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
