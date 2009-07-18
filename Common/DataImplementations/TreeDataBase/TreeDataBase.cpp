#include "TreeDataBase.h"
#include "TreeDataBasePlugin.h"

#ifdef HORUS_CLIENT
#include <QIcon>
#endif

TreeDataBase::TreeDataBase(quint32 nodeId, TreeDataBasePlugin* plugin) : TreeData(nodeId, (TreeDataPlugin*)plugin)
{
#ifdef HORUS_CLIENT
    if ( ! icons.count())
    {
        icons["DEFAULT"] = QIcon(":/Icons/DefaultIcon.png");
        icons["LESSON"] = QIcon(":/Icons/LessonIcon.png");
        icons["SUBJECT"] = QIcon(":/Icons/MatiereIcon.png");
        icons["GRADE"] = QIcon(":/Icons/ClassIcon.png");
        icons["GROUP"] = QIcon(":/Icons/GroupIcon.png");
        icons["ROOT"] = QIcon(":/Icons/RootIcon.png");
    }
#endif
}

void TreeDataBase::keyToStream(QDataStream& s)
{
    s << nodeId;
}

void TreeDataBase::dataToStream(QDataStream& s)
{
    s << userId
      << name
      << type
      << ((TreeDataBase*)(parent()))->nodeId;
}

void TreeDataBase::dataFromStream(QDataStream& s)
{
    quint32 parentId;
    s >> userId
      >> name
      >> type
      >> parentId;
    if (nodeId > 0)
        setParent( ((TreeDataBasePlugin*)(_plugin))->getNode(parentId) );
    else
        setParent(0);
    setObjectName(name);
}

QDebug TreeDataBase::operator<<(QDebug debug) const
{
    debug << getDataType() << nodeId;
    if (parent())
        debug << ((TreeDataBase*)parent())->getId();
    else
        debug << 0;
    return debug << userId << type << name;
}

#ifdef HORUS_CLIENT
QMap<QString,QIcon> TreeDataBase::icons;

QVariant TreeDataBase::data(int column, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (column == 0)
            return getId();
        if (column == 1)
            return name;
        if (column == 2)
            return type;
        if (column == 3)
            return userId;
    }
    else if (role == Qt::DecorationRole)
    {
        if (icons.contains( type ))
            return icons[ type ];
        return icons["DEFAULT"];
    }

    return QVariant();
}
#endif
#ifdef HORUS_SERVER
void TreeDataBase::fillFromDatabase(QSqlQuery& query)
{
    query.prepare("SELECT typeofnode,name,user_ref,id_parent FROM tree WHERE id=?;");
    query.addBindValue(nodeId);
    if ( ! query.exec() || ! query.next())
    {
        _error = NOT_FOUND;
        return;
    }
    type   = query.value(0).toString();
    name   = query.value(1).toString();
    userId = query.value(2).toUInt();
    setParent( ((TreeDataBasePlugin*)(_plugin))->getNode(query.value(3).toUInt()) );
//    ((TreeDataBasePlugin*)(_plugin))->getNode(query.value(4).toUInt())->setParent(this);
//    while (query.next())
//        ((TreeDataBasePlugin*)(_plugin))->getNode(query.value(4).toUInt())->setParent(this);
}

void TreeDataBase::createIntoDatabase(QSqlQuery& query)
{
    query.prepare("INSERT INTO tree (typeofnode,name,user_ref,id_parent) VALUES (?,?,?,?);");
    query.addBindValue(type);
    query.addBindValue(name);
    query.addBindValue(userId);
    query.addBindValue(parent()->getId());
    if ( ! query.exec() || ! query.next())
    {
        _error = DATABASE_ERROR;
        return;
    }
}

void TreeDataBase::saveIntoDatabase  (QSqlQuery& query)
{
    query.prepare("UPDATE tree SET typeofnode=?,name=?,user_ref=?,id_parent=? WHERE id=?;");
    query.addBindValue(type);
    query.addBindValue(name);
    query.addBindValue(userId);
    query.addBindValue(nodeId);
    if ( ! query.exec() || ! query.next())
    {
        _error = NOT_FOUND;
        return;
    }
}

void TreeDataBase::deleteFromDatabase(QSqlQuery& query)
{
    query.prepare("DELETE FROM tree WHERE id=?;");
    query.addBindValue(nodeId);
    if ( ! query.exec() || ! query.next())
    {
        _error = NOT_FOUND;
        return;
    }
}
#endif

TreeData* TreeDataBase::parent() const
{
    return (TreeData*)(QObject::parent());
}

void TreeDataBase::createChild(int userId, QString name, QString type)
{
}

void TreeDataBase::remove()
{
}

void TreeDataBase::moveTo(int idfather)
{
}

void TreeDataBase::moveTo(TreeData* father)
{
}

void TreeDataBase::setName(QString _name)
{
    name = _name;
}

void TreeDataBase::setUserId(int user)
{
    userId = user;
}

void TreeDataBase::setType(QString _type)
{
    type = _type;
}

bool TreeDataBase::isDescendantOf(int parent)
{
    return false;
}

bool TreeDataBase::isDescendantOf(TreeData* parent)
{
    return false;
}

bool TreeDataBase::canChange()
{
    return false;
}
