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
#include					"InformationsStructure.h"

#include					<QGridLayout>
#include					<QLabel>
#include					<QSortFilterProxyModel>

InformationsStructure::InformationsStructure(QWidget *parent, UserDataPlugin *userDataPlugin, TreeData *node) : QWidget(parent)
{
	QGridLayout				*layout;
	QLabel					*fieldLabel;
	QLabel					*valueLabel;
	QSortFilterProxyModel	*userFilter;
	QSortFilterProxyModel	*classFilter;

	if (!node)
		return ;
	userFilter = new QSortFilterProxyModel(this);
	userFilter->setSourceModel(userDataPlugin->listModel());
	userFilter->setFilterRole(Data::FILTER_ROLE);
	userFilter->setFilterKeyColumn(0);
	userFilter->setFilterFixedString("STUDENT");
	userFilter->setDynamicSortFilter(true);
	classFilter = new QSortFilterProxyModel(this);
	classFilter->setSourceModel(userFilter);
	classFilter->setFilterRole(Qt::UserRole);
	classFilter->setFilterKeyColumn(0);
	classFilter->setDynamicSortFilter(true);
	classFilter->setFilterRegExp(QRegExp("\\b" + QString::number(node->id()) + "\\b"));
	layout = new QGridLayout(this);
	fieldLabel = new QLabel(tr("Students number in this class"), this);
	layout->addWidget(fieldLabel, 0, 0);
	valueLabel = new QLabel(this);
	valueLabel->setNum(classFilter->rowCount());
	layout->addWidget(valueLabel, 0, 1);
}
