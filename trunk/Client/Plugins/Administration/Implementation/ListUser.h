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
#ifndef						__LISTUSER_H__
# define					__LISTUSER_H__

# include					<QWidget>

# include					<QListView>
# include					<QTableView>
# include					<QPushButton>
# include					<QBoxLayout>
# include					<QSortFilterProxyModel>

# include					"../../../../Common/TreeData.h"
# include					"../../../../Common/UserData.h"

# include					"InformationsUser.h"

class						ListUser : public QWidget
{
	Q_OBJECT

public:
	ListUser(QWidget* parent, TreeDataPlugin *treeDataPlugin, UserDataPlugin *userDataPlugin, int userLevel);

private:
	QSortFilterProxyModel	*gradeFilter;
	QSortFilterProxyModel	*classFilter;
	QSortFilterProxyModel	*userFilter;
	QListView				*classListView;
	QTableView				*userListView;
	InformationsUser		*informations;
	QPushButton				*addButton;
	QPushButton				*editButton;
	QPushButton				*deleteButton;
	QBoxLayout				*informationsLayout;

protected:
	void					showEvent(QShowEvent *event);

private slots:
	void					classSelected(const QModelIndex &current, const QModelIndex &previous);
	void					userSelected(const QModelIndex &current, const QModelIndex &previous);
	void					userAdded();
	void					userEdited();
	void					userDeleted();
	void					classUpdated(Data *data);
	void					userUpdated(Data *data);

signals:
	void					editUser(TreeData *node, UserData *user);
};

#endif
