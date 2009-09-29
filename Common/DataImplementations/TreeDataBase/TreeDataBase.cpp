#include "TreeDataBase.h"
#include "TreeDataBasePlugin.h"

#include "../../UserData.h"

TreeDataBase::TreeDataBase(quint32 nodeId, TreeDataBasePlugin* plugin) : TreeData((TreeDataPlugin*)plugin)
{
    _id = nodeId;
}

void TreeDataBase::keyToStream(QDataStream& s)
{
    s << id();
}

void TreeDataBase::dataToStream(QDataStream& s) const
{
	s << _user->id()
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

	_user = _plugin->pluginManager->findPlugin<UserDataPlugin*>()->getUser( userId );

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

		if ( ! query.exec())
	{
		_error = DATABASE_ERROR;
		qDebug() << query.lastError();
		return;
	}
	if ( ! query.next())
	{
		_error = NOT_FOUND;
		return;
	}

	_type   = query.value(0).toString();
    _name   = query.value(1).toString();
	_user	= _plugin->pluginManager->findPlugin<UserDataPlugin*>()->getUser( query.value(2).toUInt() );
	setParent( ((TreeDataPlugin*)_plugin)->getNode(query.value(3).toUInt()) );
}

void TreeDataBase::createIntoDatabase(QSqlQuery& query)
{
    query.prepare("INSERT INTO tree (typeofnode,name,user_ref,id_parent) VALUES (?,?,?,?);");
    query.addBindValue(_type);
    query.addBindValue(_name);
	query.addBindValue(_user->id());
	query.addBindValue(((TreeDataBase*)parent())->id());

	if ( ! query.exec())
	{
		_error = DATABASE_ERROR;
		qDebug() << query.lastError();
		return;
	}
}

void TreeDataBase::saveIntoDatabase  (QSqlQuery& query)
{
    query.prepare("UPDATE tree SET typeofnode=?,name=?,user_ref=?,id_parent=? WHERE id=?;");
    query.addBindValue(_type);
    query.addBindValue(_name);
	query.addBindValue(_user->id());
	query.addBindValue(((TreeDataBase*)parent())->id());
	query.addBindValue(_id);


	if ( ! query.exec())
	{
		_error = DATABASE_ERROR;
		qDebug() << query.lastError();
		return;
	}
	if ( ! query.numRowsAffected())
		_error = NOT_FOUND;
}

void TreeDataBase::deleteFromDatabase(QSqlQuery& query)
{
    query.prepare("DELETE FROM tree WHERE id=?;");
    query.addBindValue(_id);

	if ( ! query.exec())
	{
		_error = DATABASE_ERROR;
		qDebug() << query.lastError();
		return;
	}
	if ( ! query.numRowsAffected())
		_error = NOT_FOUND;
}
#endif
#ifdef HORUS_CLIENT
#include <QIcon>
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
			return _user->id();
    }
    else if (role == Qt::DecorationRole && column == 0)
    {
        static QMap<QString,QIcon> icons;
        if ( ! icons.count())
        {
            icons["DEFAULT"] = QIcon(":/Icons/DefaultIcon.png");
			icons["LESSON"]  = QIcon(":/Icons/LessonIcon.png");
            icons["SUBJECT"] = QIcon(":/Icons/SubjectIcon.png");
			icons["GRADE"]   = QIcon(":/Icons/GradeIcon.png");
			icons["GROUP"]   = QIcon(":/Icons/GroupIcon.png");
			icons["ROOT"]    = QIcon(":/Icons/RootIcon.png");
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

void TreeDataBase::recursRemove()
{
	//todo
	remove();
}

void TreeDataBase::moveTo(TreeData* par)
{
    if ( ! par || parent() == par)
        return;

    setParent(par);
}

void TreeDataBase::setName(QString name)
{
    if (_name == name)
        return;

    _name = name;
}

void TreeDataBase::setUser(UserData* user)
{
    if ( ! user || _user == user)
        return;

    _user = user;
}

void TreeDataBase::setType(const QString type)
{
    if (_type == type)
        return;

    _type = type;
}

bool TreeDataBase::isDescendantOf(TreeData* parent)
{
    for (TreeDataBase* node = this; node->_id != 0; node = ((TreeDataBase*)(node->parent())))
        if (node == parent)
            return true;
    return false;
}
