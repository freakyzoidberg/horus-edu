#include "FileManagment.h"

#include "User.h"
#include "Sql.h"
#include "../Common/Defines.h"

FileManagment::FileManagment()
{
    lastFileInfo.id = 0;
}

const CommFileInfo& FileManagment::getFileInfo(quint32 fileId)
{
    if (lastFileInfo.id == fileId)
        return lastFileInfo;

    lastFileInfo.id = 0;

    Sql con;
    QSqlQuery query(QSqlDatabase::database(con));

    query.prepare("SELECT name,mime,size,id_tree,id_owner,ctime,mtime,hash_sha1 FROM files WHERE id=?;");
    query.addBindValue(fileId);
    if ( ! query.exec() || ! query.next())
        return lastFileInfo;

    lastFileInfo.id = fileId;
    lastFileInfo.fileName = query.value(0).toString();
    lastFileInfo.mimeType = query.value(1).toString();
    lastFileInfo.size = query.value(2).toULongLong();
    lastFileInfo.nodeId = query.value(3).toUInt();
    lastFileInfo.ownerId = query.value(4).toUInt();
    lastFileInfo.ctime = query.value(5).toDateTime();
    lastFileInfo.mtime = query.value(6).toDateTime();
    lastFileInfo.hashSha1 = query.value(7).toByteArray();
    return lastFileInfo;
}

bool FileManagment::fileExist(quint32 fileId)
{
    getFileInfo(fileId);
    if (lastFileInfo.id)
        return true;
    return false;
}

const QList<CommFileInfo> FileManagment::getNodeList(quint32 nodeId)
{
    QList<CommFileInfo> list;

    Sql con;
    QSqlQuery query(QSqlDatabase::database(con));

    query.prepare("SELECT id,name,mime,size,id_owner,ctime,mtime,hash_sha1 FROM files WHERE id_tree=?;");
    query.addBindValue(nodeId);

    if (query.exec())
        while (query.next())
        {
            lastFileInfo.id = query.value(0).toUInt();
            lastFileInfo.fileName = query.value(1).toString();
            lastFileInfo.mimeType = query.value(2).toString();
            lastFileInfo.size = query.value(3).toULongLong();
            lastFileInfo.nodeId = nodeId;
            lastFileInfo.ownerId = query.value(4).toUInt();
            lastFileInfo.ctime = query.value(5).toDateTime();
            lastFileInfo.mtime = query.value(6).toDateTime();
            lastFileInfo.hashSha1 = query.value(7).toByteArray();
            list.append(lastFileInfo);
        }

    return list;
}

void FileManagment::insertNewFile(CommFileInfo& file)
{
    file.ctime = QDateTime::currentDateTime();
    file.mtime = QDateTime::currentDateTime();
    file.id = 0;
    file.size = 0;

    Sql con;
    QSqlQuery query(QSqlDatabase::database(con));

    query.prepare("INSERT INTO files (name,mime,id_owner,ctime,mtime) VALUES (?,?,?,?);");
    query.addBindValue(file.fileName);
    query.addBindValue(file.mimeType);
    query.addBindValue(file.ownerId);
    query.addBindValue(file.ctime);
    query.addBindValue(file.mtime);

    if (query.exec())
       file.id = query.lastInsertId().toUInt();
    else
        qDebug() << query.lastError();

    lastFileInfo = file;
}

const QList<CommFileInfo> FileManagment::getUserList(quint32 userId)
{
    QList<CommFileInfo> list;

    Sql con;
    QSqlQuery query(QSqlDatabase::database(con));

    query.prepare("SELECT id,name,mime,size,id_owner,ctime,mtime,hash_sha1,id_tree FROM files;");

    if (query.exec())
        while (query.next())
        {
            lastFileInfo.id = query.value(0).toUInt();
            lastFileInfo.fileName = query.value(1).toString();
            lastFileInfo.mimeType = query.value(2).toString();
            lastFileInfo.size = query.value(3).toULongLong();
            lastFileInfo.ownerId = query.value(4).toUInt();
            lastFileInfo.ctime = query.value(5).toDateTime();
            lastFileInfo.mtime = query.value(6).toDateTime();
            lastFileInfo.hashSha1 = query.value(7).toByteArray();
            lastFileInfo.nodeId = query.value(8).toUInt();
            list.append(lastFileInfo);
        }

    return list;
}

bool FileManagment::userCanReadFile(quint32 userId, quint32 fileId)
{
    getFileInfo(fileId);
    //    if ( ! userCanListNode(userId, ))
    return true;
}

bool FileManagment::userCanWriteFile(quint32 userId, quint32 fileId)
{
    return true;
}

bool FileManagment::userCanListNode(quint32 userId, quint32 nodeId)
{
    //TODO: check into the tree
    return true;
}

bool FileManagment::userCanChangeNode(quint32 userId, quint32 nodeId)
{
    if (User::getUser(userId)->getLevel() > LEVEL_ADMINISTRATOR)
        return false;

    //TODO: check into the tree

    return true;
}
