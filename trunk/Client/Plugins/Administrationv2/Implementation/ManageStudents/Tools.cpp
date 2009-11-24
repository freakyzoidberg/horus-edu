#include "Tools.h"

mytools::mytools(TreeDataPlugin *_mtreeplugin, UserDataPlugin *_muserplugin)
{
    _treeplugin = _mtreeplugin;
    _userplugin = _muserplugin;
}

QMap<int, QString> mytools::getallclass()
{
QMap<int, QString> allclass;
for (int i = 0; i < _treeplugin->allDatas().size(); ++i)
{
    TreeData    *data = qobject_cast<TreeData *>(_treeplugin->allDatas().at(i));
	if ((data->type() == "GRADE") && IS_VALID_DATA_STATUS(data->status()))
    {

        allclass.insert(data->id(), data->name());
    }
}
return allclass;
}


QList<UserData*> mytools::getStudentfromClass(int id)
{
    QList<UserData*> mylist;
	foreach (Data* data, _userplugin->allDatas())
    {
		UserData* user = (UserData*)data;
                //qDebug() << "item child : " << user->studentClass()->id() << " - " << id;
		if ((user->studentClass()->id() == id) && (user->level() == LEVEL_STUDENT) && IS_VALID_DATA_STATUS(user->status()))
        {
            mylist.append(user);
        }
    }
    return (mylist);
}

