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
    if ((data->type()) == "GRADE")
    {
        qDebug() << data->name();
        allclass.insert(data->id(), data->name());
    }
}
return allclass;
}


QList<UserData*> mytools::getStudentfromClass(int id)
{
    QList<UserData*> mylist;
    foreach (UserData* user, _userplugin->allUser())
    {
                //qDebug() << "item child : " << user->studentClass()->id() << " - " << id;
        if ((user->studentClass()->id() == id) && (user->level() == LEVEL_STUDENT))
        {
            qDebug() << id;
            mylist.append(user);
        }
    }
    return (mylist);
}

