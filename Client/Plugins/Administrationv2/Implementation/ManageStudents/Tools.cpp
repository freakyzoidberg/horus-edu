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
#include "Tools.h"

mytools::mytools(TreeDataPlugin *_mtreeplugin, UserDataPlugin *_muserplugin)
{
    _treeplugin = _mtreeplugin;
    _userplugin = _muserplugin;
}

QMap<int, QString> mytools::getallclass()
{
QMap<int, QString> allclass;
for (int i = 0; i < _treeplugin->allDatas().size(); ++i)
{
    TreeData    *data = qobject_cast<TreeData *>(_treeplugin->allDatas().at(i));
	if ((data->type() == "GRADE") && IS_VALID_DATA_STATUS(data->status()))
    {

        allclass.insert(data->id(), data->name());
    }
}
return allclass;
}


QList<UserData*> mytools::getStudentfromClass(int id)
{
    QList<UserData*> mylist;
	foreach (Data* data, _userplugin->allDatas())
    {
		UserData* user = (UserData*)data;
                //qDebug() << "item child : " << user->studentClass()->id() << " - " << id;
		if ((user->studentClass()->id() == id) && (user->level() == LEVEL_STUDENT) && IS_VALID_DATA_STATUS(user->status()))
        {
            mylist.append(user);
        }
    }
    return (mylist);
}

