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
#include		"Administration.h"

#include		<QTabWidget>

#include		"../../../../Common/TreeDataPlugin.h"
#include		"../../../../Common/UserData.h"

#include		"ManageStructure.h"
#include		"ManageUser.h"
#include		"ManageClasses/AdmAddClassWidget.h"

const QString	Administration::pluginName() const
{
    return ("Administration");
}

const QString	Administration::pluginVersion() const
{
    return ("3.0");
}

const QString	Administration::getDisplayableName() const
{
    return (tr("Administration"));
}

int				Administration::getOrder() const
{
    return (10);
}
QIcon			Administration::getIcon() const
{
    return (QIcon(":/Icons/admin.png"));
}

QWidget			*Administration::getWidget()
{
	UserData	*u;
	QTabWidget	*widget;
	
	u = pluginManager->currentUser();
	if (u && u->level() > LEVEL_ADMINISTRATOR)
		return (0);
	widget = new QTabWidget();
	widget->addTab(new AdmAddClassWidget(pluginManager->findPlugin<TreeDataPlugin *>(), pluginManager->findPlugin<UserDataPlugin *>()), QIcon(":/Icons/desk.png"), tr("Classes"));
	widget->addTab(new ManageStructure(widget, pluginManager->findPlugin<TreeDataPlugin *>(), pluginManager->findPlugin<UserDataPlugin *>()), QIcon(":/Icons/desk.png"), tr("Classes"));
	widget->addTab(new ManageUser(widget, pluginManager->findPlugin<TreeDataPlugin *>(), pluginManager->findPlugin<UserDataPlugin *>(), LEVEL_STUDENT), QIcon(":/Icons/students.png"), tr("Students"));
	widget->addTab(new ManageUser(widget, pluginManager->findPlugin<TreeDataPlugin *>(), pluginManager->findPlugin<UserDataPlugin *>(), LEVEL_TEACHER), QIcon(":/Icons/teachers.png"), tr("Teachers"));
	widget->addTab(new ManageUser(widget, pluginManager->findPlugin<TreeDataPlugin *>(), pluginManager->findPlugin<UserDataPlugin *>(), LEVEL_ADMINISTRATOR), QIcon(":/Icons/administrator.png"), tr("Administratives"));
	return (widget);
}
