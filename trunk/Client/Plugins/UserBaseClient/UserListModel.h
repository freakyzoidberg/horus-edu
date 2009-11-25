#ifndef USERLISTMODEL_H
#define USERLISTMODEL_H

#include "../../DataListModel.h"
class UserDataPlugin;

class UserListModel : public DataListModel
{
public:
	UserListModel(const UserDataPlugin* plugin);
};

#endif // USERLISTMODEL_H
