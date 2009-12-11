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
#include <QLabel>

#include "../../../../Common/TreeData.h"
#include "AdmClassListSelection.h"

AdmClassListSelection::AdmClassListSelection(PluginManager *pluginManager)
							: QWidget()
{
	this->treePlugin = pluginManager->findPlugin<TreeDataPlugin *>();
	QVBoxLayout *ListLayout = new QVBoxLayout();

	ListLayout->setMargin(0);
	ListLayout->setSpacing(0);

	ClassList = new QListWidget(this);
	ClassList->setSelectionRectVisible(false);

	QLabel *title = new QLabel(tr("Select a class to view, add or edit its time table."));
	title->setProperty("isTitle", true);
	ListLayout->addWidget(title);

	  ListLayout->addWidget(ClassList);

	   //connect(ClassList, SIGNAL(itemClicked(QListWidgetItem *)),
				//this, SLOT(updatestudents(QListWidgetItem *)));
	   this->setLayout(ListLayout);

	   fillClassList();
}

QMap<int, QString> AdmClassListSelection::getallclass()
{
	QMap<int, QString> allclass;

	for (int i = 0; i < treePlugin->allDatas().size(); ++i)
	{
		TreeData    *data = qobject_cast<TreeData *>(treePlugin->allDatas().at(i));
		if ((data->type() == "GRADE") && IS_VALID_DATA_STATUS(data->status()))
			allclass.insert(data->id(), data->name());
	}
	return allclass;
}

void	AdmClassListSelection::fillClassList()
{
	QMapIterator<int, QString> i(getallclass());
	ClassList->clear();

	while (i.hasNext())
	{
		i.next();
		QListWidgetItem *tempitem = new QListWidgetItem(QIcon(":/desk.png"), i.value());
		tempitem->setData(Qt::UserRole, i.key());
		ClassList->addItem(tempitem);
	}
}
