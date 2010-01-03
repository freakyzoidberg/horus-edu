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

#include <QVBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QList>

#include "../../../../Common/UserDataPlugin.h"
#include "../../../../Common/UserData.h"
#include "studentslist.h"

StudentsList::StudentsList(TreeData *node, PluginManager  *pluginManager, QVBoxLayout *RightLayout)
{
	_pluginManager = pluginManager;
	_node = node;

	QVBoxLayout *ListLayout = new QVBoxLayout();

	ListLayout->setMargin(0);
	ListLayout->setSpacing(0);

	_sList = new QListWidget(this);
	_sList->setSelectionRectVisible(false);

	QLabel *title = new QLabel(tr("Select a student to add, view or edit its grades."));
	title->setProperty("isTitle", true);
	ListLayout->addWidget(title);

	ListLayout->addWidget(_sList);

//	connect(_examsList, SIGNAL(itemClicked(QListWidgetItem *)),
	//		this, SLOT(selectStudents(QListWidgetItem *)));
	//connect(this->treePlugin,SIGNAL(dataUpdated(Data*)),this,SLOT(fillExamsList()));
	this->setLayout(ListLayout);
}

void	StudentsList::fillStudentList()
{
	UserDataPlugin	*users = _pluginManager->findPlugin<UserDataPlugin *>();

	_sList->clear();
	QList<Data *> usersData = users->allDatas();
	for (int i = 0; i < usersData.size(); ++i)
	{
		UserData *data = qobject_cast<UserData *>(usersData.at(i));
		if (data->studentClass() == _node->parent())
		{
			QListWidgetItem *tempitem = new QListWidgetItem(QIcon(":/desk.png"),
															data->name() + " " + data->surname());
			tempitem->setData(Qt::UserRole, data->id());
			_sList->addItem(tempitem);
		}
	}

	ExamsDataPlugin	*ep = _pluginManager->findPlugin<ExamsDataPlugin *>();
	_exam = ep->exam(_item->data(Qt::UserRole).toInt());
}

