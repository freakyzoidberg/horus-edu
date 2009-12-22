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
#include "ExamsDataBasePlugin.h"
#include "ExamsDataBase.h"

#include "../../PluginManager.h"
#include "../../Plugin.h"
#include "../../TreeData.h"
#include "../../UserData.h"

ExamsDataBasePlugin::ExamsDataBasePlugin()
{
}

ExamsData* ExamsDataBasePlugin::newExams(TreeData* parent, QString name, UserData* user)
{
	static quint32 tmpId = 0;
	tmpId--;

	ExamsDataBase* u = ((ExamsDataBase*)( exam(tmpId)) );
	u->setDate(QDate().currentDate());
	u->setComment(name);
	u->setTeacher(2);
	return u;
}

ExamsData* ExamsDataBasePlugin::exam(quint32 examId)
{
	if (examId == 0)
		return NULL;

	foreach (Data* d, _allDatas)
	{
		ExamsDataBase* u = (ExamsDataBase*)d;
		if (u->_id == examId)
			return u;
	}

	ExamsDataBase* u = new ExamsDataBase(examId, this);

	u->_date = QDate().currentDate();
	u->_comment = "";
	u->_subject = pluginManager->findPlugin<TreeDataPlugin*>()->rootNode();
	u->_teacher = 1;
	_allDatas.append(u);
	return u;
}

/*
void ExamsDataBasePlugin::recursiveTreeSearch(QList<ExamsData*>& list, TreeData* node, const QDateTime& from, const QDateTime& to)
{
	ExamsData* Exams;
	if ((Exams = node->registeredData<ExamsData*>()) && Exams->startTime() < to && Exams->endTime() > from)
		list.append(Exams);

	foreach (TreeData* child, node->children())
		recursiveTreeSearch(list, child, from, to);
}*/

Data* ExamsDataBasePlugin::dataWithKey(QDataStream& s)
{
    quint32 tmpId;
    s >> tmpId;
	return exam(tmpId);
}

bool ExamsDataBasePlugin::canLoad() const
{
	TreeDataPlugin* tree = pluginManager->findPlugin<TreeDataPlugin*>();
	if ( ! tree || ! tree->canLoad())
		return false;

#ifdef HORUS_SERVER
	QSqlQuery query = pluginManager->sqlQuery();
	if ( ! query.exec( "CREATE TABLE IF NOT EXISTS `examination` (\
	`id` INT NOT NULL  PRIMARY KEY ,\
	`id_tree` INT NOT NULL ,\
	`comment` TEXT NOT NULL ,\
	`date` DATE NOT NULL ,\
	`teacher_id` INT NOT NULL \
);")
	||
		 ! query.exec("SELECT`id`,`id_tree`,`comment`,`date`, `teacher_id` FROM `examination`;"))
	{
		qDebug() << "ExamsDataBasePlugin::canLoad()" << query.lastError();
		return false;
	}
#endif
	return Plugin::canLoad();
}

void  ExamsDataBasePlugin::load()
{
#ifdef HORUS_SERVER
	QSqlQuery query = pluginManager->sqlQuery();
	query.prepare("SELECT`id`,`id_tree`,`comment`,`date`, `teacher_id` FROM `examination`;");
	query.exec();
	while (query.next())
	{
		ExamsDataBase* Exams = (ExamsDataBase*)(exam(query.value(0).toUInt()));
		//Exams->_ = query.value(1).toInt()
		Exams->_subject = pluginManager->findPlugin<TreeDataPlugin*>()->node(query.value(1).toInt());
		Exams->_comment = query.value(2).toString();
		Exams->_date = query.value(3).toDate();
		Exams->_teacher = query.value(4).toInt();
		Exams->_status = Data::UPTODATE;
	}
#endif
	Plugin::load();
}

void  ExamsDataBasePlugin::unload()
{
	foreach (Data* d, _allDatas)
		delete (ExamsDataBase*)d;
	_allDatas.clear();
	Plugin::unload();
}

#ifdef HORUS_SERVER
QList<Data*> ExamsDataBasePlugin::datasForUpdate(UserData*, QDateTime date)
{
	QList<Data*> list;
	foreach (Data* data, _allDatas)
		if (data->lastChange() >= date && data->status() == Data::UPTODATE)
			list.append(data);
	return list;
}
#endif
#ifdef HORUS_CLIENT

void ExamsDataBasePlugin::dataHaveNewKey(Data*d, QDataStream& s)
{
	ExamsDataBase* u = ((ExamsDataBase*)(d));
	s >> u->_id;
	qDebug() << "User data Have a New Key" << u->_id;
}

#include "../../../Client/DataListModel.h"
QAbstractListModel* ExamsDataBasePlugin::listModel() const
{
	static DataListModel* _model = new DataListModel(this);
	return _model;
}
#endif

