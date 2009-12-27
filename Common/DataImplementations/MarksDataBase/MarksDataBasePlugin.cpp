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
#include "MarksDataBasePlugin.h"
#include "MarksDataBase.h"

#include "../../PluginManager.h"
#include "../../Plugin.h"
#include "../../TreeData.h"
#include "../../UserData.h"

MarksDataBasePlugin::MarksDataBasePlugin()
{
}

MarksData* MarksDataBasePlugin::newMarks(ExamsData* parent, UserData* user)
{
	static quint32 tmpId = 0;
	tmpId--;

	MarksDataBase* u = (MarksDataBase*)(mark(tmpId));
	u->setComment("");
	u->setResult("");
	u->setExam(parent);
	u->setStudent(user->id());
	return u;
}

MarksData* MarksDataBasePlugin::mark(quint32 markId)
{
	foreach (Data* d, _allDatas)
	{
		MarksDataBase* u = (MarksDataBase*)d;
		if (u->_id == markId)
			return u;
	}

	MarksDataBase* u = new MarksDataBase(markId, this);

	u->setComment("");
	u->setResult("");
	u->setExam(NULL);
	u->setStudent(0);
	return u;
}

Data* MarksDataBasePlugin::dataWithKey(QDataStream& s)
{
    quint32 tmpId;
    s >> tmpId;
	return mark(tmpId);
}

bool MarksDataBasePlugin::canLoad() const
{
#ifdef HORUS_SERVER

	QSqlQuery query = pluginManager->sqlQuery();

	if ( ! query.exec( "CREATE TABLE IF NOT EXISTS `Marks` (\
	`id` INT NOT NULL  PRIMARY KEY  AUTO_INCREMENT,\
	`exam_id` INT NOT NULL ,\
	`comment` TEXT NOT NULL ,\
	`result` TEXT NOT NULL ,\
	`student_id` INT NOT NULL \
);")
	||
		 ! query.exec("SELECT`id`,`exam_id`,`comment`,`result`,`student_id` FROM`Marks`WHERE `id`=-1;")
		)
	{

		qDebug() << "MarksDataBasePlugin::canLoad()" << query.lastError();
		return false;
	}

#endif
	return DataPlugin::canLoad();
}

void  MarksDataBasePlugin::load()
{
#ifdef HORUS_SERVER
	QSqlQuery query = pluginManager->sqlQuery();

	query.prepare("SELECT`id`,`exam_id`,`comment`,`result`,`student_id` FROM `Marks`;");
	query.exec();
	while (query.next())
	{
		MarksDataBase* Marks = (MarksDataBase*)(mark(query.value(0).toUInt()));
		if (!Marks)
			continue ;
		//Marks->_ = query.value(1).toInt()
		Marks->_exam = pluginManager->findPlugin<ExamsDataPlugin*>()->exam(query.value(1).toInt());
		Marks->_comment = query.value(2).toString();
		Marks->_result = query.value(3).toString();
		Marks->_student = query.value(4).toInt();
		Marks->_status = Data::UPTODATE;
	}
#endif
	Plugin::load();
}

void  MarksDataBasePlugin::unload()
{
	foreach (Data* d, _allDatas)
		delete (MarksDataBase*)d;
	_allDatas.clear();
	Plugin::unload();
}

#ifdef HORUS_SERVER
QList<Data*> MarksDataBasePlugin::datasForUpdate(MarksData*, QDateTime date)
{
	QList<Data*> list;
	foreach (Data* data, _allDatas)
		if (data->lastChange() >= date && data->status() == Data::UPTODATE)
			list.append(data);
	return list;
}
#endif
#ifdef HORUS_CLIENT

void MarksDataBasePlugin::dataHaveNewKey(Data*d, QDataStream& s)
{
	MarksDataBase* u = ((MarksDataBase*)(d));
	s >> u->_id;
	qDebug() << "Marks data Have a New Key" << u->_id;
}

#include "../../../Client/DataListModel.h"
QAbstractListModel* MarksDataBasePlugin::listModel() const
{
	static DataListModel* _model = new DataListModel(this);
	return _model;
}
#endif

