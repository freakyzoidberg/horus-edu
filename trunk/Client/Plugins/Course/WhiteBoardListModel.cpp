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

#include "../../../../Common/TreeData.h"
#include "../../../../Common/UserData.h"

WhiteBoardListModel::WhiteBoardListModel(PluginManager *pluginManager, UserData* user) : _pluginManager(pluginManager), _user(user)
{
	_wbDataPlugin = _pluginManager->findPlugin<WhiteBoardDataPlugin *>();
	foreach (Data* d, _wbDataPlugin->allDatas())
		if IS_VALID_DATA_STATUS(d->status())
			_list.append(d);
	connect(_wbDataPlugin, SIGNAL(dataStatusChanged(Data *)), this, SLOT(dataStatusChanged(Data *)));
}

int			WhiteBoardListModel::rowCount(const QModelIndex& parent) const
{
	if (!parent.isValid())
		return (_list.count());
	return (0);
}

QVariant	WhiteBoardListModel::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole)
	{	
		WhiteBoardData *wbData = static_cast<WhiteBoardData *>(_list[index.row()]);
		return QVariant(wbData->node()->name() + " (" + wbData->node()->user()->name() + " " + wbData->node()->user()->surname() + ")");
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

void	WhiteBoardListModel::dataStatusChanged(Data *data)
{
	if IS_VALID_DATA_STATUS(data->status())
	{
		if ( ! _list.contains(data))
		{
			int pos = _list.count();
			beginInsertRows(QModelIndex(), pos, pos);
			_list.append(data);
			endInsertRows();
		}
		else
		{
			QModelIndex i = index(_list.indexOf(data), 0, QModelIndex());
			changePersistentIndex(i, i);
		}
	}
	else
	{
		if (_list.contains(data))
		{
			int pos = _list.indexOf(data);
			beginRemoveRows(QModelIndex(), pos, pos);
			_list.removeOne(data);
			endRemoveRows();
		}
	}
}
