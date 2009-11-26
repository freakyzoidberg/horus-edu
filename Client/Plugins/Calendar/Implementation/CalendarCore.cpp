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
#include <QStringList>

#include "CalendarCore.h"

CalendarCore    *CalendarCore::_instance = NULL;

CalendarCore::CalendarCore(TreeDataPlugin *_tree,
                           UserDataPlugin *_users)
{
    this->tree  = _tree;
    this->users = _users;
}

CalendarCore    *CalendarCore::CalendarCoreInstance(TreeDataPlugin *treePlugin,
                                                    UserDataPlugin *userPlugin)
{
   if (!_instance)
     _instance = new CalendarCore(treePlugin, userPlugin);
   return _instance;
}

QHash<quint32, TreeData *>  *CalendarCore::getNodeOfType(QString type)
{
    QHash<quint32, TreeData *>  *classes = new QHash<quint32, TreeData *>;

    for (int i = 0; i < tree->allDatas().size(); ++i)
    {
        TreeData    *tmp = qobject_cast<TreeData *>(tree->allDatas().at(i));
        if ((tmp->type()) == type)
            classes->insert(tmp->id(), tmp);
    }
   return classes;
}

 QList<UserData*> CalendarCore::usersName(const QString & groupName)
 {
	QList<UserData *>  list;
	foreach (Data* data, users->allDatas())
	{
		UserData* user = (UserData*)data;
		if (IS_VALID_DATA_STATUS(user->status()) && (groupName == "ALL" || user->studentClass()->name() == groupName))
			list.append(user);
    }
   return list;
 }


