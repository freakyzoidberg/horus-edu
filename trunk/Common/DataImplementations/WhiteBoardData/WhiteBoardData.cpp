#include "WhiteBoardData.h"
#include "WhiteBoardDataPlugin.h"
#include "../../PluginManager.h"
#include "../../TreeData.h"

void WhiteBoardData::keyToStream(QDataStream& s)
{
	s << ((TreeData*)parent())->id();
}

void WhiteBoardData::dataToStream(QDataStream& s) const
{
	s << (quint16)(_items.count());
	foreach (const WhiteBoardItem& item, _items)
		item >> s;

	Data::dataToStream(s);
}

void WhiteBoardData::dataFromStream(QDataStream& s)
{
	_items.clear();

	quint16 nbItems;
	s >> nbItems;

	for (quint16 pos = 0; pos < nbItems; pos++)
		_items.append( WhiteBoardItem(s) );

	Data::dataFromStream(s);
}

QDebug WhiteBoardData::operator<<(QDebug debug) const
{
	return debug << "WhiteBoardData::" << ((TreeData*)parent())->id();
}

#ifdef HORUS_CLIENT
#include <QIcon>
QVariant WhiteBoardData::data(int column, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (column == 0)
			return ((TreeData*)parent())->id();
        if (column == 1)
			return tr("White Board");
    }
//    else if (role == Qt::DecorationRole && column == 0)
//    {
//        return QIcon(":/user.ico");
//    }
    return QVariant();
}
#endif

#ifdef HORUS_SERVER
void WhiteBoardData::fillFromDatabase(QSqlQuery& query)
{
//    query.prepare("SELECT login,level,last_login,surname,name,birth_date,picture,address,phone,country,language,id_tree,enabled,mtime FROM users WHERE id=?;");
//    query.addBindValue(_id);
//    if ( ! query.exec() || ! query.next())
//    {
//        _error = NOT_FOUND;
//        return;
//    }
//    _login      = query.value(0).toString();
//    _level      = (UserLevel)(query.value(1).toUInt());
//    _lastLogin  = query.value(2).toDateTime();
//    _surname    = query.value(3).toString();
//    _name       = query.value(4).toString();
//    _birthDate  = query.value(5).toDate();
//    _picture    = query.value(6).toByteArray();
//    _address    = query.value(7).toString();
//    _phone      = query.value(8).toString();
//    _country    = query.value(9).toString();
//    _language   = query.value(10).toString();
//    TreeDataPlugin* treePlugin = _plugin->pluginManager->findPlugin<TreeDataPlugin*>();
//    if (treePlugin)
//        _node = treePlugin->getNode( query.value(11).toUInt() );
//    else
//        _node = 0;
//    _enabled    = query.value(12).toBool();
//    _lastChange= query.value(13).toDateTime();
}

void WhiteBoardData::createIntoDatabase(QSqlQuery& query)
{
//    query.prepare("INSERT INTO users (login,level,last_login,surname,name,birth_date,picture,address,phone,country,language,id_tree,enabled,mtime,password) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?);");
//    query.addBindValue(_login);
//    query.addBindValue(_level);
//    query.addBindValue(_lastLogin);
//    query.addBindValue(_surname);
//    query.addBindValue(_name);
//    query.addBindValue(_birthDate);
//    query.addBindValue(_picture);
//    query.addBindValue(_address);
//    query.addBindValue(_phone);
//    query.addBindValue(_country);
//    query.addBindValue(_language);
//    if (_node)
//        query.addBindValue(_node->id());
//    else
//        query.addBindValue(0);
//    query.addBindValue(_enabled);
//    _lastChange = QDateTime::currentDateTime();
//    query.addBindValue(_lastChange);
//
//	query.addBindValue("7c4a8d09ca3762af61e59520943dc26494f8941b"); // 123456
//
//	if ( ! query.exec())
//	{
//		_error = DATABASE_ERROR;
//		qDebug() << query.lastError();
//	}
//
//	_id = query.lastInsertId().toUInt();
}

void WhiteBoardData::saveIntoDatabase(QSqlQuery& query)
{
//    query.prepare("UPDATE users SET login=?,level=?,last_login=?,surname=?,name=?,birth_date=?,picture=?,address=?,phone=?,country=?,language=?,id_tree=?,enabled=?,mtime=? WHERE id=?;");
//    query.addBindValue(_login);
//    query.addBindValue(_level);
//    query.addBindValue(_lastLogin);
//    query.addBindValue(_surname);
//    query.addBindValue(_name);
//    query.addBindValue(_birthDate);
//    query.addBindValue(_picture);
//    query.addBindValue(_address);
//    query.addBindValue(_phone);
//    query.addBindValue(_country);
//    query.addBindValue(_language);
//    if (_node)
//        query.addBindValue(_node->id());
//    else
//        query.addBindValue(0);
//    query.addBindValue(_enabled);
//    _lastChange = QDateTime::currentDateTime();
//    query.addBindValue(_lastChange);
//    query.addBindValue(_id);
//
//    if ( ! query.exec())
//    {
//        _error = NOT_FOUND;
//		qDebug() << query.lastError();
//    }
}

void WhiteBoardData::deleteFromDatabase(QSqlQuery& query)
{
//    query.prepare("DELETE FROM users WHERE id=?;");
//    query.addBindValue(_id);
//    if ( ! query.exec() || ! query.next())
//    {
//        _error = NOT_FOUND;
//        return;
//    }
}
#endif
