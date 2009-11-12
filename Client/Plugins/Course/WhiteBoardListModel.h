#ifndef WHITEBOARDLISTMODEL_H
#define WHITEBOARDLISTMODEL_H

#include <QAbstractListModel>

#include "../../../Common/PluginManager.h"
#include "../../../Common/UserData.h"
#include "../../../Common/DataImplementations/WhiteBoardData/WhiteBoardData.h"

class WhiteBoardListModel : public QAbstractListModel
{
public:
	WhiteBoardListModel(PluginManager *pluginManager, UserData* user);

	int			rowCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant	data(const QModelIndex& index, int role = Qt::DisplayRole) const;

private:
	WhiteBoardDataPlugin*	_wbDataPlugin;
	PluginManager*			_pluginManager;
	UserData*				_user;
};

#endif // WHITEBOARDLISTMODEL_H
