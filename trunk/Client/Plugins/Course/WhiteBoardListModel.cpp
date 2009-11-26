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
#include <QIcon>

#include "WhiteBoardListModel.h"

WhiteBoardListModel::WhiteBoardListModel(PluginManager *pluginManager, UserData* user) : _pluginManager(pluginManager), _user(user)
{
	_wbDataPlugin = _pluginManager->findPlugin<WhiteBoardDataPlugin *>();
}

int			WhiteBoardListModel::rowCount(const QModelIndex& parent) const
{
	if (!parent.isValid())
		return _wbDataPlugin->allDatas().count();
	return 0;
}

QVariant	WhiteBoardListModel::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole)
	{		
            return QVariant(tr("Class #") + QString::number(index.row()));
	}
        else if (role == Qt::DecorationRole)
        {
            return QVariant(QIcon(":/Ui/desk.png"));
        }
	return QVariant();
}

WhiteBoardData*     WhiteBoardListModel::getWhiteboard(const QModelIndex& index)
{
    WhiteBoardData* wbdata = qobject_cast<WhiteBoardData*>(_wbDataPlugin->allDatas().at(index.row()));
    return wbdata;
}
