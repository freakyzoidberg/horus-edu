#include "FileDataBase.h"
#include "FileDataBasePlugin.h"

#include "../../UserData.h"
#include "../../TreeData.h"
#include "../../PluginManager.h"

#ifdef HORUS_CLIENT
#include <QDir>
#include <QSettings>
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
      << _mimeType;
}

void FileDataBase::dataFromStream(QDataStream& s)
{
    quint32 ownerId;
    quint32 nodeId;

    s >> _id
      >> _name
      >> ownerId
      >> nodeId
      >> _mimeType;

    _owner = _plugin->pluginManager->findPlugin<UserDataPlugin*>()->getUser(ownerId);
    _node = _plugin->pluginManager->findPlugin<TreeDataPlugin*>()->getNode(nodeId);
#ifdef HORUS_CLIENT
    // now automaticaly download after each update
    download();
#endif
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

void FileDataBase::saveIntoDatabase  (QSqlQuery& query)
{
//    query.prepare("UPDATE File SET typeofnode=?,name=?,user_ref=?,id_parent=? WHERE id=?;");
//    query.addBindValue(type);
//    query.addBindValue(name);
//    query.addBindValue(userId);
//    query.addBindValue(nodeId);
//    if ( ! query.exec() || ! query.next())
//    {
//        _error = NOT_FOUND;
//        return;
//    }
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
    return new QFile("./Files/"+QVariant(_id).toString());
#endif
#ifdef HORUS_CLIENT
    QSettings settings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat);
    return new QFile(settings.value("General/TmpDir", QDir::tempPath()).toString()+'/'+QVariant(_id).toString());
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
}

void FileDataBase::moveTo(TreeData* node)
{
}

#ifdef HORUS_CLIENT
int FileDataBase::progress() const
{
    //TODO
    return 0;
}

void FileDataBase::downloadFinished()
{
    _file.close();
    emit downloaded();
}

void FileDataBase::uploadFinished()
{
    _file.close();
    emit uploaded();
}

void FileDataBase::connectToServer(const QByteArray& key)
{
    qDebug() << "File::connectToServer(" << key.toHex() << ")";

    _socket.setProtocol(QSsl::SslV3);
    _socket.setPeerVerifyMode(QSslSocket::VerifyNone);

    QSettings settings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat);
    _socket.connectToHostEncrypted(settings.value("Network/Server", "localhost").toString(),
                                     settings.value("Network/PortTransfert", 42042).toInt());
    _socket.waitForEncrypted();
    _socket.write(key);
    _socket.flush();
}

void FileDataBase::downloadAuthorized(const QByteArray& key)
{
    _file.open(QIODevice::ReadWrite | QIODevice::Truncate);
    connect(&_socket, SIGNAL(readyRead()), this, SLOT(connexionReadyRead()));
    connect(&_socket, SIGNAL(disconnected()), this, SLOT(downloadFinished()));
    connectToServer(key);
}

void FileDataBase::uploadAuthorized(const QByteArray& key)
{
    _file.open(QIODevice::ReadOnly);
    connect(&_socket, SIGNAL(bytesWritten(quint64)), this, SLOT(connexionByteWritten(quint64)));
    connect(&_socket, SIGNAL(disconnected()), this, SLOT(uploadFinished()));
    connectToServer(key);
}

void FileDataBase::connexionReadyRead()
{
    qDebug() << "File::connexionReadyRead()";

    QByteArray buff = _socket.readAll();
    if ( ! buff.length())
        return;

    _file.write(buff);
}

void FileDataBase::connexionBytesWritten(qint64 len)
{
    qDebug() << "File::connexionByteWritten(" << len << ")";
    QByteArray buff = _file.read(8192);
    if (buff.length())
        _socket.write(buff);
    else
        _socket.close();
}

void FileDataBase::download()
{
    qDebug() << "File::download()";
    _netPlugin->askForDownload(this);
}

void FileDataBase::upload()
{
    qDebug() << "File::upload()";
    _netPlugin->askForUpload(this);
}
#endif
