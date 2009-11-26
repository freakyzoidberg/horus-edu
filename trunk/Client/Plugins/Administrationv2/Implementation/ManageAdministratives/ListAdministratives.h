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
#ifndef				__LISTADMINISTRATIVES_H__
# define			__LISTADMINISTRATIVES_H__

# include			<QWidget>

# include			<QListView>
# include			<QPushButton>
# include			<QBoxLayout>
# include			<QSortFilterProxyModel>

# include			"../../../../../Common/PluginManager.h"
# include			"../../../../../Common/UserData.h"
# include			"DisplayAdministrative.h"

class				ListAdministratives : public QWidget
{
	Q_OBJECT

public:
	ListAdministratives(QWidget *parent, PluginManager *pluginManager);
	QListView		*listView;

private:
	DisplayAdministrative	*displayer;
	QPushButton		*editButton;
	QPushButton		*deleteButton;
	QSortFilterProxyModel	*filter;
	QBoxLayout		*informationsLayout;
	PluginManager	*_pluginManager;

private slots:
	void			AdministrativeSelected(const QModelIndex &current, const QModelIndex &previous);
	void			AdministrativeAdded();
	void			AdministrativeEdited();
	void			AdministrativeDeleted();
	void			AdministrativeUpdated(Data *data);

signals:
	void			editAdministrative(UserData *user);
};

#endif
