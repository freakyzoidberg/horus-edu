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
#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
class Data;
class TreeData;
class TreeDataPlugin;

class TreeModel : public QAbstractItemModel
{
	Q_OBJECT
public:
	TreeModel(const TreeDataPlugin* plugin);
	int							rowCount(const QModelIndex &parent = QModelIndex()) const;
	int							columnCount(const QModelIndex &parent = QModelIndex()) const;
	QModelIndex					parent(const QModelIndex &child) const;
	QModelIndex					index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
	QVariant					data(const QModelIndex &index, int role = Qt::DisplayRole) const;
private slots:
	void						dataStatusChanged(Data* data);
private:
	void						inserData(TreeData* parent, Data* data);
	void						removeData(TreeData* parent, Data* data);
	const TreeDataPlugin*		_plugin;
	QMultiHash<TreeData*,Data*>	_data;
};

#endif // TREEMODEL_H
