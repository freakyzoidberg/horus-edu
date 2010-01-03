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
#include		"Marks.h"
#include		"MarksMainView.h"

const QString	Marks::pluginName() const
{
	return ("Marks");
}

const QString	Marks::pluginVersion() const
{
	return ("0.1");
}

QWidget			*Marks::getWidget()
{
	MarksMainView	*mainView = new MarksMainView(pluginManager);

	return mainView;
}

const QString       Marks::getDisplayableName() const
{
	return(tr("Marks"));
}

int					Marks::getOrder() const
{
	return 48;
}

bool                Marks::canLoad() const
{
	return true;
}

void                Marks::load()
{

/*	treePlugin = pluginManager->findPlugin<TreeDataPlugin*>();
	userPlugin = pluginManager->findPlugin<UserDataPlugin *>();
	eventPlugin = pluginManager->findPlugin<EventDataPlugin *>();
	//    schedulePlugin = pluginManager->findPlugin<ScheduleDataPlugin*>(); */

	_examsPlugin = pluginManager->findPlugin<ExamsDataPlugin *>();
	_currentUser = pluginManager->currentUser();

	Plugin::load();
}

QIcon				Marks::getIcon() const
{
  return QIcon(":/marks_backup.png");
}

