#include "FileDataBase.h"
#include "FileDataBasePlugin.h"

#ifdef HORUS_CLIENT
#include <QIcon>
#endif

FileDataBase::FileDataBase(quint32 nodeId, FileDataBasePlugin* plugin) : FileData(nodeId, (FileDataPlugin*)plugin)
{
#ifdef HORUS_CLIENT
    if ( ! icons.count())
    {
        icons["DEFAULT"] = QIcon(":/Icons/DefaultIcon.png");
        icons["LESSON"] = QIcon(":/Icons/LessonIcon.png");
        icons["SUBJECT"] = QIcon(":/Icons/SubjectIcon.png");
        icons["GRADE"] = QIcon(":/Icons/GradeIcon.png");
        icons["GROUP"] = QIcon(":/Icons/GroupIcon.png");
        icons["ROOT"] = QIcon(":/Icons/RootIcon.png");
    }
#endif
}

void FileDataBase::keyToStream(QDataStream& s)
{
    s << nodeId;
}

void FileDataBase::dataToStream(QDataStream& s)
{
    s << userId
      << name
      << type;
    if (nodeId > 0)
        s << ((FileDataBase*)(parent()))->nodeId;
}

void FileDataBase::dataFromStream(QDataStream& s)
{
    quint32 parentId;
    s >> userId
      >> name
      >> type
      >> parentId;
    if (nodeId > 0)
        setParent( ((FileDataBasePlugin*)(_plugin))->getNode(parentId) );
    else
        setParent(0);
    setObjectName(name);
}

QDebug FileDataBase::operator<<(QDebug debug) const
{
    debug << getDataType() << nodeId;
    if (parent())
        debug << ((FileDataBase*)parent())->getId();
    else
        debug << 0;
    return debug << userId << type << name;
}

#ifdef HORUS_SERVER
void FileDataBase::fillFromDatabase(QSqlQuery& query)
{
    query.prepare("SELECT typeofnode,name,user_ref,id_parent FROM File WHERE id=?;");
    query.addBindValue(nodeId);
    if ( ! query.exec() || ! query.next())
    {
        _error = NOT_FOUND;
        return;
    }
    type   = query.value(0).toString();
    name   = query.value(1).toString();
    userId = query.value(2).toUInt();
    setParent( ((FileDataBasePlugin*)(_plugin))->getNode(query.value(3).toUInt()) );
//    ((FileDataBasePlugin*)(_plugin))->getNode(query.value(4).toUInt())->setParent(this);
//    while (query.next())
//        ((FileDataBasePlugin*)(_plugin))->getNode(query.value(4).toUInt())->setParent(this);
}

void FileDataBase::createIntoDatabase(QSqlQuery& query)
{
    query.prepare("INSERT INTO File (typeofnode,name,user_ref,id_parent) VALUES (?,?,?,?);");
    query.addBindValue(type);
    query.addBindValue(name);
    query.addBindValue(userId);
    query.addBindValue(((FileDataBase*)parent())->getId());
    if ( ! query.exec() || ! query.next())
    {
        _error = DATABASE_ERROR;
        return;
    }
}

void FileDataBase::saveIntoDatabase  (QSqlQuery& query)
{
    query.prepare("UPDATE File SET typeofnode=?,name=?,user_ref=?,id_parent=? WHERE id=?;");
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

void FileDataBase::deleteFromDatabase(QSqlQuery& query)
{
    query.prepare("DELETE FROM File WHERE id=?;");
    query.addBindValue(nodeId);
    if ( ! query.exec() || ! query.next())
    {
        _error = NOT_FOUND;
        return;
    }
}
#endif
#ifdef HORUS_CLIENT
QMap<QString,QIcon> FileDataBase::icons;

QVariant FileDataBase::data(int column, int role) const
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
    else if (role == Qt::DecorationRole && column == 0)
    {
        if (icons.contains( type ))
            return icons[ type ];
        return icons["DEFAULT"];
    }
   else if (role == Qt::BackgroundColorRole)
   {
       if (status() == UPTODATE)
           return QColor(210, 255, 210);//green : uptodate
       if (status() == SAVING || status() == CREATING)
           return QColor(210, 210, 255);//blue : saving & creating
       if (status() == DELETING)
           return QColor(255, 210, 210);//red : deleting

       return QColor(220, 220, 220);//gray : cached, updating, ...
   }

   return QVariant();
}
#endif

void FileDataBase::createChild(int userId, QString name, QString type)
{
}

void FileDataBase::remove()
{
    setStatus(Data::DELETING);
}

void FileDataBase::moveTo(int idfather)
{
    preSaveData();
}

void FileDataBase::moveTo(FileData* father)
{
    preSaveData();
    setParent(father);
    setStatus(Data::SAVING);
}

void FileDataBase::setName(QString _name)
{
    preSaveData();
    name = _name;
    setStatus(Data::SAVING);
}

void FileDataBase::setUserId(int user)
{
    preSaveData();
    userId = user;
    setStatus(Data::SAVING);
}

void FileDataBase::setType(QString _type)
{
    preSaveData();
    type = _type;
    setStatus(Data::SAVING);
}

bool FileDataBase::isDescendantOf(int parent)
{
    return false;
}

bool FileDataBase::isDescendantOf(FileData* parent)
{
    return false;
}

bool FileDataBase::canChange()
{
    return false;
}
