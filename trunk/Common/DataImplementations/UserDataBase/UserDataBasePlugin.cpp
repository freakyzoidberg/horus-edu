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
#include "UserDataBasePlugin.h"
#include "UserDataBase.h"

#include "../../TreeData.h"

#include "../../PluginManager.h"
#include "../../Plugin.h"

UserDataBasePlugin::UserDataBasePlugin()
{
	_nobody = new UserDataBase(0, this);
}

void UserDataBasePlugin::load()
{
	UserDataBase* n = ((UserDataBase*)(_nobody));
	n->setStudent(_nobody);
	n->_level = __LAST_LEVEL__;
	n->_name = tr("Nobody");
	n->_surname = tr("Nobody");
	n->_login = tr("Nobody");
	n->_status = Data::UPTODATE;
	n->setStudentClass(pluginManager->findPlugin<TreeDataPlugin*>()->rootNode());
#ifdef HORUS_SERVER
	QSqlQuery query = pluginManager->sqlQuery();
        query.prepare("SELECT`enabled`,`login`,`level`,`password`,`student_class`,`last_login`,`language`,`surname`,`name`,`birth_date`,`picture`,`address`,`phone1`,`phone2`,`phone3`,`country`,`gender`,`occupation`,`pro_category`,`relationship`,`student`,`mail`,`subscription_reason`,`repeated_years`,`start_year`,`leave_year`,`follow_up`,`comment`,`born_place`,`nbr_brothers`,`social_insurance_nbr`,`diploma`,`contract`,`mtime`,`id`, `passmail` FROM`user`;");

	if ( ! query.exec())
	{
		qDebug() << query.lastError();
		return;
	}
	while (query.next())
	{
		UserDataBase* u = (UserDataBase*)(user(query.value(34).toUInt()));

		u->_enabled				= query.value( 0).toBool();
		u->_login				= query.value( 1).toString();
		u->_level				= (UserLevel)(query.value(2).toUInt());
		u->_password			= QByteArray::fromHex(query.value(3).toByteArray());
		u->_studentClass		= pluginManager->findPlugin<TreeDataPlugin*>()->node( query.value(4).toUInt() );
		u->_lastLogin			= query.value( 5).toDateTime();
		u->_language			= query.value( 6).toString();
		u->_surname				= query.value( 7).toString();
		u->_name				= query.value( 8).toString();
		u->_birthDate			= query.value( 9).toDate();
		u->_picture				= query.value(10).toByteArray();
		u->_address				= query.value(11).toString();
		u->_phone1				= query.value(12).toString();
		u->_phone2				= query.value(13).toString();
		u->_phone3				= query.value(14).toString();
		u->_country				= query.value(15).toString();
		u->_gender				= (UserGender)(query.value(16).toUInt());
		u->_occupation			= query.value(17).toString();
		u->_proCategory			= query.value(18).toString();
		u->_relationship		= query.value(19).toString();
		u->setStudent(			  pluginManager->findPlugin<UserDataPlugin*>()->user( query.value(20).toUInt() ));
		u->_mail				= query.value(21).toString();
		u->_subscriptionReason	= query.value(22).toString();
		u->_repeatedYears		= query.value(23).toUInt();
		u->_startYear			= query.value(24).toUInt();
		u->_leaveYear			= query.value(25).toUInt();
		u->_followUp			= query.value(26).toString();
		u->_comment				= query.value(27).toString();
		u->_bornPlace			= query.value(28).toString();
		u->_nbrBrothers			= query.value(29).toUInt();
		u->_socialInsuranceNbr	= query.value(30).toString();
		u->_diploma				= query.value(32).toString();
		u->_contract			= query.value(32).toString();
		u->_lastChange			= query.value(33).toDateTime();
                u->_mailpassword                = query.value(35).toString();
		u->_status				= Data::UPTODATE;

		disconnect(u, SLOT(studentClassRemoved()));
		connect(u->_studentClass, SIGNAL(removed()), u, SLOT(studentClassRemoved()));
	}
#endif
	Plugin::load();
}

void UserDataBasePlugin::unload()
{
	foreach (Data* d, _allDatas)
		delete (UserDataBase*)d;
	_allDatas.clear();
	DataPlugin::unload();
}

bool UserDataBasePlugin::canLoad() const
{
#ifdef HORUS_SERVER
	QSqlQuery query = pluginManager->sqlQuery();
	if ( ! query.exec("CREATE TABLE IF NOT EXISTS`user`(\
						`id`int(11) NOT NULL auto_increment,\
						`enabled`tinyint(1) NOT NULL,\
						`login`varchar(32) NOT NULL,\
						`level`tinyint(1) NOT NULL,\
						`password`char(40) NOT NULL,\
						`student_class`int(11) default NULL,\
						`session_key`char(64) default NULL,\
						`session_end`timestamp NULL default NULL,\
						`last_login`timestamp NULL default NULL,\
						`language`varchar(32) default NULL,\
						`surname`varchar(255) default NULL,\
						`name`varchar(255) default NULL,\
						`birth_date`timestamp NULL default NULL,\
						`picture`blob,\
						`address`varchar(255) default NULL,\
						`phone1`varchar(32) default NULL,\
						`phone2`varchar(32) default NULL,\
						`phone3`varchar(32) default NULL,\
						`country`varchar(32) default NULL,\
						`gender`tinyint(1) default NULL,\
						`occupation`varchar(32) default NULL,\
						`pro_category`varchar(32) default NULL,\
						`relationship`varchar(32) default NULL,\
						`student`int(11) default NULL,\
						`mail`varchar(32) default NULL,\
						`subscription_reason`varchar(32) default NULL,\
						`repeated_years`int(11) default NULL,\
						`start_year`int(11) default NULL,\
						`leave_year`int(11) default NULL,\
						`follow_up`text default NULL,\
						`comment`text default NULL,\
						`born_place`varchar(32) default NULL,\
						`nbr_brothers`int(11) default NULL,\
						`social_insurance_nbr`varchar(32) default NULL,\
						`diploma`varchar(255) default NULL,\
						`contract`varchar(255) default NULL,\
						`passmail`varchar(40) default NULL,\
						`mtime`timestamp NOT NULL,\
						PRIMARY KEY(`id`),\
						KEY`level`(`level`),\
						KEY`login`(`login`),\
						KEY`enabled`(`enabled`),\
						KEY`student_class`(`student_class`),\
						KEY`student`(`student`)\
					);")
		||
		 ! query.exec("SELECT`enabled`,`login`,`level`,`password`,`student_class`,`last_login`,`language`,`surname`,`name`,`birth_date`,`picture`,`address`,`phone1`,`phone2`,`phone3`,`country`,`gender`,`occupation`,`pro_category`,`relationship`,`student`,`mail`,`subscription_reason`,`repeated_years`,`start_year`,`leave_year`,`follow_up`,`comment`,`born_place`,`nbr_brothers`,`social_insurance_nbr`,`diploma`,`contract`,`mtime`,`id`FROM`user`WHERE`id`=-1;")
		)
	{
		qDebug() << "UserDataBasePlugin::canLoad()" << query.lastError();
		return false;
	}
#endif
	return DataPlugin::canLoad();
}

QList<UserData*> UserDataBasePlugin::parentsOfStudent(const UserData* student) const
{
	QList<UserData*> list;
	foreach (Data* d, _allDatas)
	{
		UserDataBase* u = (UserDataBase*)d;
		if (u->_student == student)
			list.append(u);
	}
	return list;
}

UserData* UserDataBasePlugin::user(quint32 userId)
{
	if (userId == 0)
		return nobody();

	foreach (Data* d, _allDatas)
	{
		UserDataBase* u = (UserDataBase*)d;
		if (u->_id == userId)
			return u;
	}

	UserDataBase* u = new UserDataBase(userId, this);

	u->setStudentClass(pluginManager->findPlugin<TreeDataPlugin*>()->rootNode());
	u->setStudent(_nobody);

	_allDatas.append(u);
	return u;
}

UserData* UserDataBasePlugin::user(const QString login)
{
	foreach (Data* d, _allDatas)
	{
		UserDataBase* u = (UserDataBase*)d;
		if (u->_login == login)
			return u;
	}
	return 0;
}

Data* UserDataBasePlugin::dataWithKey(QDataStream& s)
{
    quint32 tmpId;
    s >> tmpId;
	return user(tmpId);
}

UserData* UserDataBasePlugin::createUser(const QString &login)
{
	static quint32 tmpId = 0;
	tmpId--;

	UserDataBase* u = ((UserDataBase*)( user(tmpId)) );
	u->_login = login;
	u->setName("New user");
	u->setSurname("New user");
    return u;
}

#ifdef HORUS_CLIENT
void UserDataBasePlugin::dataHaveNewKey(Data*d, QDataStream& s)
{
	UserDataBase* u = ((UserDataBase*)(d));
	s >> u->_id;
	qDebug() << "User data Have a New Key" << u->_id;
}

#include "../../../Client/DataListModel.h"
QAbstractListModel* UserDataBasePlugin::listModel() const
{
	static DataListModel* _model = new DataListModel(this);
	return _model;
}
#endif
