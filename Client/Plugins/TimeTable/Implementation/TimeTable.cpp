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

#include		"TimeTable.h"
/*#include "../../../../Common/TreeDataPlugin.h"
#include "../../../../Common/UserData.h"
#include "../../../../Common/EventData.h" */
//#include "../../../../Common/ScheduleData.h"

/* */

 /* */

#include "MainView.h"

const QString		TimeTable::pluginName() const
{
	return "TimeTable";
}

const QString		TimeTable::pluginVersion() const
{
	return "0.1";
}

QWidget				*TimeTable::getWidget()
{

   currentUser = pluginManager->currentUser();
 //   if (u != 0)
   //     return new MainView(pluginManager);
   // return NULL;
	return new MainView(pluginManager);
}

const QString       TimeTable::getDisplayableName() const
{
    return(tr("TimeTable"));
}

int					TimeTable::getOrder() const
{
	return 102;
}

bool                TimeTable::canLoad() const
{
	return true;
}

void                TimeTable::load()
{
/*	treePlugin = pluginManager->findPlugin<TreeDataPlugin*>();
	userPlugin = pluginManager->findPlugin<UserDataPlugin *>();
	eventPlugin = pluginManager->findPlugin<EventDataPlugin *>();
	//    schedulePlugin = pluginManager->findPlugin<ScheduleDataPlugin*>(); */
	Plugin::load();
}

QIcon				TimeTable::getIcon() const
{
  return QIcon(":/TimeTable.png");
}
