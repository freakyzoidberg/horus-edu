#include "TreeDataBase.h"
#include "TreeDataBasePlugin.h"

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
//QMap<QString,QIcon> TreeDataBase::icons;
//TreeDataBase::icons["DEFAULT"] = QIcon(":/Icons/DefaultIcon.png");
//TreeDataBase::icons["LESSON"] = QIcon(":/Icons/LessonIcon.png");
//TreeDataBase::icons["SUBJECT"] = QIcon(":/Icons/MatiereIcon.png");
//TreeDataBase::icons["GRADE"] = QIcon(":/Icons/ClassIcon.png");
//TreeDataBase::icons["GROUP"] = QIcon(":/Icons/GroupIcon.png");
//TreeDataBase::icons["ROOT"] = QIcon(":/Icons/RootIcon.png");

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

    return QVariant();
}
#endif
#ifdef HORUS_SERVER
void TreeDataBase::fillFromDatabase(QSqlQuery& query)
{
    query.prepare("SELECT p.typeofnode,p.name,p.user_ref,p.id_parent,c.id FROM tree p LEFT JOIN tree c ON c.id_parent=p.id WHERE p.id=?;");
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
    ((TreeDataBasePlugin*)(_plugin))->getNode(query.value(4).toUInt())->setParent(this);
    while (query.next())
        ((TreeDataBasePlugin*)(_plugin))->getNode(query.value(4).toUInt())->setParent(this);
}

void TreeDataBase::createIntoDatabase(QSqlQuery& TODO)
{
}

void TreeDataBase::saveIntoDatabase  (QSqlQuery& TODO)
{
}

void TreeDataBase::deleteFromDatabase(QSqlQuery& TODO)
{
}
#endif

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
