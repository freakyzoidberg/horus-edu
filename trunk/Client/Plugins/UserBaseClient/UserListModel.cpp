#include "UserListModel.h"
#include "../../../Common/UserData.h"
#include <QMimeData>
#include <QDataStream>

UserListModel::UserListModel(const UserDataPlugin* plugin) : DataListModel(plugin) {}

