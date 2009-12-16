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
#include	"ManageUser.h"

ManageUser::ManageUser(QWidget *parent, TreeDataPlugin *treeDataPlugin, UserDataPlugin *userDataPlugin, int userLevel) : QWidget(parent), _treeDataPlugin(treeDataPlugin), _userDataPlugin(userDataPlugin), _userLevel(userLevel)
{
	layout = new QHBoxLayout(this);
	layout->setSpacing(0);
	layout->setMargin(0);
	list = new ListUser(this, treeDataPlugin, userDataPlugin, userLevel);
	layout->addWidget(list);
	edit = 0;
	connect(list, SIGNAL(editUser(TreeData *, UserData *)), this, SLOT(userEdited(TreeData *, UserData *)));
}

ManageUser::~ManageUser()
{
	if (edit)
	{
		disconnect(edit, SIGNAL(exit()), this, SLOT(editExited()));
		delete edit;
	}
	else
		disconnect(list, SIGNAL(editUser(TreeData *, UserData *)), this, SLOT(userEdited(TreeData *, UserData *)));
	delete list;
	delete layout;
}

void		ManageUser::userEdited(TreeData *node, UserData *user)
{
	disconnect(list, SIGNAL(editUser(TreeData *, UserData *)), this, SLOT(userEdited(TreeData *, UserData *)));
	list->hide();
	edit = new EditUser(this, _userDataPlugin, _userLevel, node, user);
	layout->addWidget(edit);
	connect(edit, SIGNAL(exit()), this, SLOT(editExited()));
}

void		ManageUser::editExited()
{
	disconnect(edit, SIGNAL(exit()), this, SLOT(editExited()));
	delete edit;
	edit = 0;
	list->show();
	connect(list, SIGNAL(editUser(TreeData *, UserData *)), this, SLOT(userEdited(TreeData *, UserData *)));
}
