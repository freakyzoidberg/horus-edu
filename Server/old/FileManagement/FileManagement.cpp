#include "FileManagement.h"
#include "../../../Common/Defines.h"
#include <QDebug>
#include <QHash>

Q_EXPORT_PLUGIN2(FileManagement, FileManagement)

FileManagement::FileManagement()
{
    requestFunctions["create"] = &FileManagement::createRequest;
    requestFunctions["access"] = &FileManagement::accessRequest;
    requestFunctions["list"] = &FileManagement::listRequest;
}

bool FileManagement::start()
{
    thread = new ThreadFiles(this);
    return true;
}

void FileManagement::recvPacket(quint32 userId, const PluginPacket& request)
{
    PluginPacket response(request.sourcePlugin, request.request);

    QVariantHash reqHash = request.data.toHash();

    (this->*requestFunctions.value(request.request,//go to the target method
                                   &FileManagement::unknownRequest)) //or if it'sunknown request
                                                                   (userId, reqHash, response);//parameters

    //send response
    server->sendPacket(userId, response);
}

void FileManagement::unknownRequest(quint32, const QVariantHash&, PluginPacket& response)
{
    response.error          = 1;
    response.errorMessage   = "Unknow request.";
}

void FileManagement::createRequest(quint32, const QVariantHash&, PluginPacket&)
{
}

void FileManagement::accessRequest(quint32, const QVariantHash&, PluginPacket&)
{
}

void FileManagement::listRequest(quint32, const QVariantHash&, PluginPacket& resp)
{
    QSqlQuery query = server->getSqlQuery();
    query.prepare("SELECT id,name,mime,size,id_owner,ctime,mtime,hash_sha1,id_tree FROM files;"); //TODO WHERE....
    if ( ! query.exec())
    {
        resp.error = 1;
        resp.errorMessage = "Database error.";
        return;
    }

    QVariantList list;
    while (query.next())
    {
        QVariantHash info;
        info["id"]    = query.value(0).toUInt();
        info["name"]  = query.value(1).toString();
        info["mime"]  = query.value(2).toString();
        info["size"]  = query.value(3).toULongLong();
        info["owner"] = query.value(4).toUInt();
        info["ctime"] = query.value(5).toDateTime();
        info["mtime"] = query.value(6).toDateTime();
        info["sha1"]  = query.value(7).toByteArray();
        info["node"]  = query.value(8).toUInt();
        list.append(info);
    }
    resp.data = list;
}

//const FileInfo& FileManagment::getFileInfo(quint32 fileId)
//{
//    if (lastFileInfo.id == fileId)
//        return lastFileInfo;
//
//    lastFileInfo.id = 0;
//
//    Sql con;
//    QSqlQuery query(QSqlDatabase::database(con));
//
//    query.prepare("SELECT name,mime,size,id_tree,id_owner,ctime,mtime,hash_sha1 FROM files WHERE id=?;");
//    query.addBindValue(fileId);
//    if ( ! query.exec() || ! query.next())
//        return lastFileInfo;
//
//    lastFileInfo.id = fileId;
//    lastFileInfo.fileName = query.value(0).toString();
//    lastFileInfo.mimeType = query.value(1).toString();
//    lastFileInfo.size = query.value(2).toULongLong();
//    lastFileInfo.nodeId = query.value(3).toUInt();
//    lastFileInfo.ownerId = query.value(4).toUInt();
//    lastFileInfo.ctime = query.value(5).toDateTime();
//    lastFileInfo.mtime = query.value(6).toDateTime();
//    lastFileInfo.hashSha1 = query.value(7).toByteArray();
//    return lastFileInfo;
//}
//
//bool FileManagment::fileExist(quint32 fileId)
//{
//    getFileInfo(fileId);
//    if (lastFileInfo.id)
//        return true;
//    return false;
//}
//
//const QList<FileInfo> FileManagment::getNodeList(quint32 nodeId)
//{
//    QList<FileInfo> list;
//
//    Sql con;
//    QSqlQuery query(QSqlDatabase::database(con));
//
//    query.prepare("SELECT id,name,mime,size,id_owner,ctime,mtime,hash_sha1 FROM files WHERE id_tree=?;");
//    query.addBindValue(nodeId);
//
//    if (query.exec())
//        while (query.next())
//        {
//            lastFileInfo.id = query.value(0).toUInt();
//            lastFileInfo.fileName = query.value(1).toString();
//            lastFileInfo.mimeType = query.value(2).toString();
//            lastFileInfo.size = query.value(3).toULongLong();
//            lastFileInfo.nodeId = nodeId;
//            lastFileInfo.ownerId = query.value(4).toUInt();
//            lastFileInfo.ctime = query.value(5).toDateTime();
//            lastFileInfo.mtime = query.value(6).toDateTime();
//            lastFileInfo.hashSha1 = query.value(7).toByteArray();
//            list.append(lastFileInfo);
//        }
//
//    return list;
//}
//
//void FileManagment::insertNewFile(FileInfo& file)
//{
//    file.ctime = QDateTime::currentDateTime();
//    file.mtime = QDateTime::currentDateTime();
//    file.id = 0;
//    file.size = 0;
//
//    Sql con;
//    QSqlQuery query(QSqlDatabase::database(con));
//
//    query.prepare("INSERT INTO files (name,mime,id_owner,ctime,mtime) VALUES (?,?,?,?);");
//    query.addBindValue(file.fileName);
//    query.addBindValue(file.mimeType);
//    query.addBindValue(file.ownerId);
//    query.addBindValue(file.ctime);
//    query.addBindValue(file.mtime);
//
//    if (query.exec())
//       file.id = query.lastInsertId().toUInt();
//    else
//        qDebug() << query.lastError();
//
//    lastFileInfo = file;
//}
//
//const QList<FileInfo> FileManagment::getUserList(quint32 userId)
//{
//    QList<FileInfo> list;
//
//    Sql con;
//    QSqlQuery query(QSqlDatabase::database(con));
//
//    query.prepare("SELECT id,name,mime,size,id_owner,ctime,mtime,hash_sha1,id_tree FROM files;");
//
//    if (query.exec())
//        while (query.next())
//        {
//            lastFileInfo.id = query.value(0).toUInt();
//            lastFileInfo.fileName = query.value(1).toString();
//            lastFileInfo.mimeType = query.value(2).toString();
//            lastFileInfo.size = query.value(3).toULongLong();
//            lastFileInfo.ownerId = query.value(4).toUInt();
//            lastFileInfo.ctime = query.value(5).toDateTime();
//            lastFileInfo.mtime = query.value(6).toDateTime();
//            lastFileInfo.hashSha1 = query.value(7).toByteArray();
//            lastFileInfo.nodeId = query.value(8).toUInt();
//            list.append(lastFileInfo);
//        }
//
//    return list;
//}
//
//bool FileManagment::userCanReadFile(quint32 userId, quint32 fileId)
//{
//    getFileInfo(fileId);
//    //    if ( ! userCanListNode(userId, ))
//    return true;
//}
//
//bool FileManagment::userCanWriteFile(quint32 userId, quint32 fileId)
//{
//    return true;
//}
//
//bool FileManagment::userCanListNode(quint32 userId, quint32 nodeId)
//{
//    //TODO: check into the tree
//    return true;
//}
//
//bool FileManagment::userCanChangeNode(quint32 userId, quint32 nodeId)
//{
//    if (User::getUser(userId)->getLevel() > LEVEL_ADMINISTRATOR)
//        return false;
//
//    //TODO: check into the tree
//
//    return true;
//}
