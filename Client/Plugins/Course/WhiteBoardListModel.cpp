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
		WhiteBoardData* wbdata = qobject_cast<WhiteBoardData*>(_wbDataPlugin->allDatas().at(index.row()));
		return QVariant("Class #" + index.row());
	}
	return QVariant();
}
