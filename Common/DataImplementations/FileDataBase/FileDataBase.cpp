#include "FileDataBase.h"
#include "FileDataBasePlugin.h"

#include "../../UserData.h"
#include "../../TreeData.h"
#include "../../PluginManager.h"

FileDataBase::FileDataBase(quint32 nodeId, FileDataBasePlugin* plugin) : FileData(nodeId, (FileDataPlugin*)plugin)
{
}

void FileDataBase::keyToStream(QDataStream& s)
{
    s << id;
}

void FileDataBase::dataToStream(QDataStream& s)
{
    s << id
      << name
      << user->id()
      << node->id()
      << mimeType;
}

void FileDataBase::dataFromStream(QDataStream& s)
{
    quint32 userId;
    quint32 nodeId;

    s >> id
      >> name
      >> userId
      >> nodeId
      >> mimeType;

    user = _plugin->pluginManager->findPlugin<UserDataPlugin*>()->getUser(userId);
    node = _plugin->pluginManager->findPlugin<TreeDataPlugin*>()->getNode(nodeId);

    setObjectName(name);
}

QDebug FileDataBase::operator<<(QDebug debug) const
{
    return debug
      << id
      << name
      << user->id()
      << node->id()
      << mimeType;
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
#ifdef HORUS_CLIENT
QVariant FileDataBase::data(int column, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (column == 0)
            return id;
        if (column == 1)
            return name;
        if (column == 2)
            return mimeType;
        if (column == 3)
            return user->id();
        if (column == 4)
            return node->id();
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
