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
    _isDownloaded = false;
    _netPlugin = plugin->pluginManager->findPlugin<FileNetworkPlugin*>("File Network Plugin");
    QSettings settings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat);
    _file.setFileName(settings.value("General/TmpDir", QDir::tempPath()).toString()+'/'+QVariant(_id).toString());
#endif
}
void FileDataBase::keyToStream(QDataStream& s)
{
    s << _id;
}

void FileDataBase::dataToStream(QDataStream& s)
{
    s << _id
      << _name
      << _owner->id()
      << _node->id()
      << _mimeType
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
      >> hash;

    _owner = _plugin->pluginManager->findPlugin<UserDataPlugin*>()->getUser(ownerId);
    _node = _plugin->pluginManager->findPlugin<TreeDataPlugin*>()->getNode(nodeId);
#ifdef HORUS_CLIENT
    if (hash.isEmpty() || hash.isEmpty() || hash != _hash)
        download();
#endif
    _hash = hash;
}

QDebug FileDataBase::operator<<(QDebug debug) const
{
    return debug
      << _id
      << _name
      << _owner->id()
      << _node->id()
      << _mimeType;
}

#ifdef HORUS_SERVER
void FileDataBase::fillFromDatabase(QSqlQuery& query)
{
//    query.prepare("SELECT typeofnode,name,user_ref,id_parent FROM File WHERE id=?;");
//    query.addBindValue(nodeId);
//    if ( ! query.exec() || ! query.next())
//    {
//        _error = NOT_FOUND;
//        return;
//    }
//    type   = query.value(0).toString();
//    name   = query.value(1).toString();
//    userId = query.value(2).toUInt();
//    setParent( ((FileDataBasePlugin*)(_plugin))->getNode(query.value(3).toUInt()) );
//    ((FileDataBasePlugin*)(_plugin))->getNode(query.value(4).toUInt())->setParent(this);
//    while (query.next())
//        ((FileDataBasePlugin*)(_plugin))->getNode(query.value(4).toUInt())->setParent(this);
}

void FileDataBase::createIntoDatabase(QSqlQuery& query)
{
//    query.prepare("INSERT INTO File (typeofnode,name,user_ref,id_parent) VALUES (?,?,?,?);");
//    query.addBindValue(type);
//    query.addBindValue(name);
//    query.addBindValue(userId);
//    query.addBindValue(((FileDataBase*)parent())->getId());
//    if ( ! query.exec() || ! query.next())
//    {
//        _error = DATABASE_ERROR;
//        return;
//    }
}

void FileDataBase::saveIntoDatabase(QSqlQuery& query)
{
    query.prepare("UPDATE files SET name=?,mime=?,size=?,id_tree=?,id_owner=?,mtime=?,hash_sha1=? WHERE id=?;");
    query.addBindValue(_name);
    query.addBindValue(_mimeType);
    query.addBindValue(_size);
    query.addBindValue(node()->id());
    query.addBindValue(owner()->id());
    _lastChange = QDateTime::currentDateTime();
    query.addBindValue(_lastChange);
    query.addBindValue(_hash.toHex());
    query.addBindValue(_id);
    if ( ! query.exec())
    {
        _error = NOT_FOUND;
        return;
    }
}

void FileDataBase::deleteFromDatabase(QSqlQuery& query)
{
//    query.prepare("DELETE FROM File WHERE id=?;");
//    query.addBindValue(nodeId);
//    if ( ! query.exec() || ! query.next())
//    {
//        _error = NOT_FOUND;
//        return;
//    }
}
#endif

QFile* FileDataBase::file() const
{
#ifdef HORUS_SERVER
    return new QFile(QSettings().value("SETTINGS/FilesDirectory").toString()+'/'+QVariant(_id).toString());
#endif
#ifdef HORUS_CLIENT
    QFile* f = new QFile(_file.fileName());
    connect(f, SIGNAL(aboutToClose()),this, SLOT(calculateHash()));
    return f;
#endif
}

#ifdef HORUS_CLIENT
QVariant FileDataBase::data(int column, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (column == 0)
            return _id;
        if (column == 1)
            return _name;
        if (column == 2)
            return _mimeType;
        if (column == 3)
            return _owner->id();
        if (column == 4)
            return _node->id();
    }
    else if (role == Qt::DecorationRole && column == 0)
    {
//        if (icons.contains( type ))
//            return icons[ type ];
//        return icons["DEFAULT"];
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

void FileDataBase::moveTo(TreeData* node)
{
    if ( ! node || _node == node)
        return;

    _node = node;
}

#ifdef HORUS_CLIENT
void FileDataBase::download()
{
    qDebug() << "File::download()";
    _netPlugin->askForDownload(this);
    _isDownloaded = false;
}

bool FileDataBase::isDownloaded() const
{
    return _isDownloaded;
}

void FileDataBase::downloadAuthorized(const QByteArray& key)
{
    _transfertKey = key;
    _file.open(QIODevice::ReadWrite | QIODevice::Truncate);
    connect(&_socket, SIGNAL(readyRead()), this, SLOT(connexionReadyRead()));
    connect(&_socket, SIGNAL(disconnected()), this, SLOT(downloadFinished()));
    connectToServer();
}

void FileDataBase::connexionReadyRead()
{
    qDebug() << "File::connexionReadyRead()";

    QByteArray buff = _socket.readAll();
    if ( ! buff.length())
        return;

    _file.write(buff);
}

void FileDataBase::downloadFinished()
{
    _file.close();
    disconnect(&_socket, SIGNAL(readyRead()), this, SLOT(connexionReadyRead()));
    disconnect(&_socket, SIGNAL(disconnected()), this, SLOT(downloadFinished()));
    _isDownloaded = true;
    emit downloaded();
}

void FileDataBase::upload()
{
    qDebug() << "File::upload()";
    _netPlugin->askForUpload(this);
}

void FileDataBase::uploadAuthorized(const QByteArray& key)
{
    _transfertKey = key;
    _file.open(QIODevice::ReadOnly);
    connect(&_socket, SIGNAL(bytesWritten(qint64)), this, SLOT(connexionBytesWritten(qint64)));
    connect(&_socket, SIGNAL(disconnected()), this, SLOT(uploadFinished()));
    connectToServer();
}

void FileDataBase::connexionBytesWritten(qint64 len)
{
    qDebug() << "File::connexionByteWritten(" << len << ")";
    QByteArray buff = _file.read(8192);
    if (buff.length())
    {
        _socket.write(buff);
        _socket.flush();
    }
    else
        _socket.close();
}

void FileDataBase::uploadFinished()
{
    _file.close();
    disconnect(&_socket, SIGNAL(bytesWritten(qint64)), this, SLOT(connexionBytesWritten(qint64)));
    disconnect(&_socket, SIGNAL(disconnected()), this, SLOT(uploadFinished()));
    emit uploaded();
}

int FileDataBase::progress() const
{
    //TODO
    return 0;
}

void FileDataBase::connectToServer()
{
    qDebug() << "File::connectToServer()";

    _socket.setProtocol(QSsl::SslV3);
    _socket.setPeerVerifyMode(QSslSocket::VerifyNone);

    connect(&_socket, SIGNAL(encrypted()), this, SLOT(connexionEncrypted()));

    QSettings settings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat);
    _socket.connectToHostEncrypted(settings.value("Network/Server", "localhost").toString(),
                                     settings.value("Network/PortTransfert", 42042).toInt());
}

void FileDataBase::connexionEncrypted()
{
    disconnect(&_socket, SIGNAL(encrypted()), this, SLOT(connexionEncrypted()));
    _socket.write(_transfertKey);
    _socket.flush();
}

void FileDataBase::calculateHash()
{
    QCryptographicHash h(QCryptographicHash::Sha1);

    _file.open(QIODevice::ReadOnly);
    while ( ! _file.atEnd())
        h.addData( _file.read(8192) );
    _file.close();

    _hash = h.result();
}
#endif
