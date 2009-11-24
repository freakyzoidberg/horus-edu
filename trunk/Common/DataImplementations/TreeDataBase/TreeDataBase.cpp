#include "TreeDataBase.h"
#include "TreeDataBasePlugin.h"

#include "../../UserData.h"

TreeDataBase::TreeDataBase(quint32 nodeId, TreeDataBasePlugin* plugin) : TreeData((TreeDataPlugin*)plugin)
{
	moveToThread(plugin->thread());
	_id = nodeId;
	_parent = 0;
	connect(this, SIGNAL(removed()), this, SLOT(thisRemoved()), Qt::DirectConnection);
}

void TreeDataBase::userRemoved()
{
	disconnect(_user, SIGNAL(removed()), this, SLOT(userRemoved()));
	_user = _plugin->pluginManager->findPlugin<UserDataPlugin*>()->nobody();
	connect(_user, SIGNAL(removed()), this, SLOT(userRemoved()));
}

void TreeDataBase::thisRemoved()
{
	//remove from the tree
	setParent(0);
}

void TreeDataBase::keyToStream(QDataStream& s) const
{
	s << _id;
}

void TreeDataBase::dataToStream(QDataStream& s) const
{
	s << _user->id()
      << _name
      << _type;
	if (_parent)
		s << _parent->_id;
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

	if (this != ((TreeDataBasePlugin*)(_plugin))->rootNode())
		setParent((TreeDataBase*)((TreeDataBasePlugin*)(_plugin))->node(parentId));
    else
		setParent(0);

	disconnect(_user, SIGNAL(removed()), this, SLOT(userRemoved()));
	_user = _plugin->pluginManager->findPlugin<UserDataPlugin*>()->user( userId );
	connect(_user, SIGNAL(removed()), this, SLOT(userRemoved()));

    setObjectName(_name);
}

bool TreeDataBase::canChange(UserData* user) const
{	//canChange if admin or if user referent of this node or a parent
	if (user->level() <= LEVEL_ADMINISTRATOR || _user == user)
		return true;
	if (_parent)
		return _parent->canChange(user);
	return false;
}

bool TreeDataBase::canAccess(UserData* user) const
{//canAccess if canChange or has class one of the parents
	if (canChange(user) || user->studentClass() == this)
		return true;
	for (TreeData* pos = user->studentClass(); pos->parent(); pos = pos->parent())
		if (pos->canAccess(user))
			return true;

	return false;
}

QDebug TreeDataBase::operator<<(QDebug debug) const
{
	debug << dataType() << _id;
    if (parent())
        debug << ((TreeDataBase*)parent())->_id;
    else
        debug << 0;
    return debug << _type << _name;
}

const QList<Data*> TreeDataBase::dependsOfCreatedData() const
{
	QList<Data*> list;
	list.append(_user);
	list.append(_parent);
	return list;
}

#ifdef HORUS_SERVER
quint8 TreeDataBase::serverRead()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("SELECT`typeofnode`,`name`,`user_ref`,`id_parent`,`mtime`FROM`tree`WHERE`id`=?;");
    query.addBindValue(_id);

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
	if ( ! query.next())
		return NOT_FOUND;

	_type   = query.value(0).toString();
    _name   = query.value(1).toString();
	disconnect(this, SLOT(userRemoved()));
	_user	= _plugin->pluginManager->findPlugin<UserDataPlugin*>()->user( query.value(2).toUInt() );
	connect(_user, SIGNAL(removed()), this, SLOT(userRemoved()));
	setParent( ((TreeDataPlugin*)_plugin)->node(query.value(3).toUInt()) );
	_lastChange = query.value(4).toDateTime();

	return NONE;
}

quint8 TreeDataBase::serverCreate()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("INSERT INTO`tree`(`typeofnode`,`name`,`user_ref`,`id_parent`)VALUES(?,?,?,?);");
    query.addBindValue(_type);
    query.addBindValue(_name);
	query.addBindValue(_user->id());
	query.addBindValue(((TreeDataBase*)parent())->id());

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}

	_id = query.lastInsertId().toUInt();

	return NONE;
}

quint8 TreeDataBase::serverSave()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("UPDATE`tree`SET`typeofnode`=?,`name`=?,`user_ref`=?,`id_parent`=? WHERE`id`=?;");
    query.addBindValue(_type);
    query.addBindValue(_name);
	query.addBindValue(_user->id());
	query.addBindValue(((TreeDataBase*)parent())->id());
	query.addBindValue(_id);

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
	return NONE;
}

quint8 TreeDataBase::serverRemove()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("DELETE FROM`tree`WHERE`id`=?;");
    query.addBindValue(_id);

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}
	if ( ! query.numRowsAffected())
		return NOT_FOUND;

	return NONE;
}
#endif
#ifdef HORUS_CLIENT
#include <QIcon>
QVariant TreeDataBase::data(int column, int role) const
{
	if (role == Qt::DisplayRole)
    {
		if (column == -1)
            return _id;
		if (column == 0)
            return _name;
		if (column == 1)
            return _type;
		if (column == 2)
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
	QMutexLocker M(&mutex);
	TreeData* node = ((TreeDataBasePlugin*)_plugin)->createNode();
	node->setName(name);
	node->setType(type);
	node->setUser(user);
	node->setParent(this);
	node->create();
	return node;
}

void TreeDataBase::setName(QString name)
{
	QMutexLocker M(&mutex);
    _name = name;
}

void TreeDataBase::setUser(UserData* user)
{
	QMutexLocker M(&mutex);
	disconnect(_user, SIGNAL(removed()), this, SLOT(userRemoved()));
	_user = user;
	connect(_user, SIGNAL(removed()), this, SLOT(userRemoved()));
}

void TreeDataBase::setType(const QString type)
{
	QMutexLocker M(&mutex);
    _type = type;
}

void TreeDataBase::setParent(TreeData* p)
{
	QMutexLocker M(&mutex);

	if (_parent)
	{
		_parent->_children.removeOne(this);
		disconnect(_parent, SIGNAL(removed()), this, SLOT(remove()));
	}

	_parent = ((TreeDataBase*)p);
	if (_parent)
	{
		_parent->_children.append(this);
		connect(_user, SIGNAL(removed()), this, SLOT(remove()));
	}
}

bool TreeDataBase::isDescendantOf(TreeData* parent)
{
    for (TreeDataBase* node = this; node->_id != 0; node = ((TreeDataBase*)(node->parent())))
        if (node == parent)
            return true;
    return false;
}
