#include "FileDataBase.h"
#include "FileDataBasePlugin.h"

#include "../../UserData.h"
#include "../../TreeData.h"
#include "../../PluginManager.h"

#ifdef HORUS_CLIENT
#include <QSslSocket>
#include "../../../Client/Plugins/FileBaseClient/FileNetworkPlugin.h"
#include "FileBase.h"
#endif
#ifdef HORUS_SERVER
#include "../../../Server/Plugins/FileBaseServer/FileNetworkPlugin.h"
#endif

FileDataBase::FileDataBase(quint32 fileId, FileDataBasePlugin* plugin) : FileData(plugin)
{
    _id = fileId;
#ifdef HORUS_CLIENT
    _device = new FileBase(this, plugin->pluginManager->findPlugin<FileNetworkPlugin*>("File Network Plugin"));
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
    device()->download();
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

QFile* FileDataBase::device() const
{
    return new QFile("./Files/"+QVariant(_id).toString());
}
#endif
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
