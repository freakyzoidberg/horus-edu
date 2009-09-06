#include "TreeDataBase.h"
#include "TreeDataBasePlugin.h"

#ifdef HORUS_CLIENT
#include <QIcon>
#endif

TreeDataBase::TreeDataBase(quint32 nodeId, TreeDataBasePlugin* plugin) : TreeData(nodeId, (TreeDataPlugin*)plugin)
{
}

void TreeDataBase::keyToStream(QDataStream& s)
{
    s << id();
}

void TreeDataBase::dataToStream(QDataStream& s)
{
    s << (quint32)0//_user->id()
      << _name
      << _type;
    if (_id > 0)
        s << ((TreeDataBase*)(parent()))->_id;
    else
        s << (quint32)0;
}

void TreeDataBase::dataFromStream(QDataStream& s)
{
    quint32 parentId, userId;
    s >> userId
      >> _name
      >> _type
      >> parentId;
    if (_id > 0)
        setParent( ((TreeDataBasePlugin*)(_plugin))->getNode(parentId) );
    else
        setParent(0);

//    _user = _plugin->pluginManager->

    setObjectName(_name);
}

QDebug TreeDataBase::operator<<(QDebug debug) const
{
    debug << getDataType() << _id;
    if (parent())
        debug << ((TreeDataBase*)parent())->_id;
    else
        debug << 0;
    return debug << _type << _name;
}

#ifdef HORUS_SERVER
void TreeDataBase::fillFromDatabase(QSqlQuery& query)
{
    query.prepare("SELECT typeofnode,name,user_ref,id_parent FROM tree WHERE id=?;");
    query.addBindValue(_id);
    if ( ! query.exec() || ! query.next())
    {
        _error = NOT_FOUND;
        return;
    }
    _type   = query.value(0).toString();
    _name   = query.value(1).toString();
    //_userId = query.value(2).toUInt();
    setParent( ((TreeDataBasePlugin*)(_plugin))->getNode(query.value(3).toUInt()) );
//    ((TreeDataBasePlugin*)(_plugin))->getNode(query.value(4).toUInt())->setParent(this);
//    while (query.next())
//        ((TreeDataBasePlugin*)(_plugin))->getNode(query.value(4).toUInt())->setParent(this);
}

void TreeDataBase::createIntoDatabase(QSqlQuery& query)
{
    query.prepare("INSERT INTO tree (typeofnode,name,user_ref,id_parent) VALUES (?,?,?,?);");
    query.addBindValue(_type);
    query.addBindValue(_name);
    query.addBindValue(0);
    query.addBindValue(((TreeDataBase*)parent())->_id);
    if ( ! query.exec() || ! query.next())
    {
        _error = DATABASE_ERROR;
        return;
    }
}

void TreeDataBase::saveIntoDatabase  (QSqlQuery& query)
{
    query.prepare("UPDATE tree SET typeofnode=?,name=?,user_ref=?,id_parent=? WHERE id=?;");
    query.addBindValue(_type);
    query.addBindValue(_name);
    query.addBindValue(0);
    query.addBindValue(_id);
    if ( ! query.exec() || ! query.next())
    {
        _error = NOT_FOUND;
        return;
    }
}

void TreeDataBase::deleteFromDatabase(QSqlQuery& query)
{
    query.prepare("DELETE FROM tree WHERE id=?;");
    query.addBindValue(_id);
    if ( ! query.exec() || ! query.next())
    {
        _error = NOT_FOUND;
        return;
    }
}
#endif
#ifdef HORUS_CLIENT
QVariant TreeDataBase::data(int column, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (column == 0)
            return _id;
        if (column == 1)
            return _name;
        if (column == 2)
            return _type;
        if (column == 3)
            return 0;//user->id()
    }
    else if (role == Qt::DecorationRole && column == 0)
    {
        static QMap<QString,QIcon> icons;
        if ( ! icons.count())
        {
            icons["DEFAULT"] = QIcon(":/Icons/DefaultIcon.png");
            icons["LESSON"] = QIcon(":/Icons/LessonIcon.png");
            icons["SUBJECT"] = QIcon(":/Icons/SubjectIcon.png");
            icons["GRADE"] = QIcon(":/Icons/GradeIcon.png");
            icons["GROUP"] = QIcon(":/Icons/GroupIcon.png");
            icons["ROOT"] = QIcon(":/Icons/RootIcon.png");
        }
        if (icons.contains( _type ))
            return icons[ _type ];
        return icons["DEFAULT"];
    }
   return Data::data(column, role);
}
#endif

TreeData* TreeDataBase::createChild(const QString name, const QString type, UserData* user)
{
    return 0;
}

void TreeDataBase::remove()
{
    setStatus(Data::DELETING);
}

void TreeDataBase::moveTo(TreeData* parent)
{
    setParent(parent);
    setStatus(Data::SAVING);
}

void TreeDataBase::setName(QString name)
{
    _name = name;
    setStatus(Data::SAVING);
}

void TreeDataBase::setUser(UserData* user)
{
    _user = user;
    setStatus(Data::SAVING);
}

void TreeDataBase::setType(const QString type)
{
    _type = type;
    setStatus(Data::SAVING);
}

bool TreeDataBase::isDescendantOf(TreeData* parent)
{
    return false;
}
