#include <QStringList>

#include "CalendarCore.h"

CalendarCore    *CalendarCore::_instance = NULL;

CalendarCore::CalendarCore(TreeDataPlugin *_tree,
                           UserDataPlugin *_users)
{
    this->tree  = _tree;
    this->users = _users;
}

CalendarCore    *CalendarCore::CalendarCoreInstance(TreeDataPlugin *treePlugin, UserDataPlugin *userPlugin)
{
   if (!_instance)
     _instance = new CalendarCore(treePlugin, userPlugin);
   return _instance;
}

QHash<quint32, TreeData *>  *CalendarCore::getNodeOfType(QString type)
{
    QHash<quint32, TreeData *>  *classes = new QHash<quint32, TreeData *>;

    for (int i = 0; i < tree->allDatas().size(); ++i)
    {
        TreeData    *tmp = qobject_cast<TreeData *>(tree->allDatas().at(i));
        if ((tmp->type()) == type)
            classes->insert(tmp->id(), tmp);
    }
   return classes;
}

 QStringList CalendarCore::usersName(QHash<quint32, TreeData *> *groups)
 {
    QStringList userNames;

    for (int i = 0; i < users->getAllUser().size(); ++i)
       userNames.append(users->getAllUser().value(i)->login());
    return userNames;
 }
