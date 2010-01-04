/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "TreeDataBase.h"
#include "TreeDataBasePlugin.h"

#include "../../UserData.h"
#include "../../FileData.h"

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
	QList<TreeData*> children = _children;

	//temporary link children to the grand parent
	foreach (TreeData* child, children)
		child->setParent(_parent);

	//remove the node from the tree
	setParent(0);

	//also remove chidren
	foreach (TreeData* child, children)
		child->remove();
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

	Data::dataToStream(s);
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

	Data::dataFromStream(s);
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
	return true;
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
quint8 TreeDataBase::serverCreate()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("INSERT INTO`tree`(`typeofnode`,`name`,`user_ref`,`id_parent`)VALUES(?,?,?,?);");
    query.addBindValue(_type);
    query.addBindValue(_name);
	query.addBindValue(_user->id());
	query.addBindValue((TreeDataBase*)parent() ? ((TreeDataBase*)parent())->id() : 0);

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return DATABASE_ERROR;
	}

	_id = query.lastInsertId().toUInt();
	if (_type == "ROOT")
	{
		QSqlQuery query = _plugin->pluginManager->sqlQuery();
		query.prepare("UPDATE`tree`SET`id`=? WHERE`id`=?;");
		query.addBindValue(0);
		query.addBindValue(_id);
		if ( ! query.exec())
		{
			qDebug() << query.lastError();
			return DATABASE_ERROR;
		}
		_id = 0;
	}
	return NONE;
}

quint8 TreeDataBase::serverSave()
{
	QSqlQuery query = _plugin->pluginManager->sqlQuery();
	query.prepare("UPDATE`tree`SET`typeofnode`=?,`name`=?,`user_ref`=?,`id_parent`=? WHERE`id`=?;");
    query.addBindValue(_type);
    query.addBindValue(_name);
	query.addBindValue(_user->id());
	query.addBindValue((TreeDataBase*)parent() ? ((TreeDataBase*)parent())->id() : 0);
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
	if (role == FILTER_ROLE)
	{
		if (column == 0)
			return _type;
		if (column == 1 && _parent)
			return _parent->id();
	}
	else if (role == Qt::DisplayRole)
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
		return icon();

	return QVariant();
}

const QIcon TreeDataBase::icon() const
{
	static QMap<QString,QIcon> icons;
	if ( ! icons.count())
	{
		icons["DEFAULT"] = QIcon(":/Icons/DefaultIcon.png");
		icons["LESSON"]  = QIcon(":/Icons/LessonIcon.png");
		icons["SUBJECT"] = QIcon(":/subject.png");
		icons["GRADE"]   = QIcon(":/desk.png");
		icons["GROUP"]   = QIcon(":/Icons/GroupIcon.png");
		icons["ROOT"]    = QIcon(":/school.png");
	}
	if (icons.contains( _type ))
		return icons[ _type ];
	return icons["DEFAULT"];
}

#include "../../FileData.h"
#include "../../UserData.h"
#include <QUrl>
#include <QFileInfo>
bool TreeDataBase::dropData(const QList<Data*> list, Qt::DropAction)
{
	foreach (Data* data, list)
	{
		UserData* user;
		if ((user = qobject_cast<UserData*>(data)))
		{
			if (user->level() == LEVEL_STUDENT && type() == "GRADE")
			{
				user->setStudentClass(this);
				user->save();
			}
			else if (user->level() <= LEVEL_TEACHER)
			{
				setUser(user);
				save();
			}
			continue;
		}

		FileData* file;
		if ((file = qobject_cast<FileData*>(data)))
		{
			file->moveTo(this);
			file->save();
			continue;
		}
	}
	return true;
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
	if (this == parent)
		return true;

	if ( ! _parent)
		return false;

	return _parent->isDescendantOf(parent);
}

bool TreeDataBase::isInSubject(const QString subject)
{
	if (_type == "SUBJECT" && _name == subject)
		return true;

	if ( ! _parent)
		return false;

	return _parent->isInSubject(subject);
}
