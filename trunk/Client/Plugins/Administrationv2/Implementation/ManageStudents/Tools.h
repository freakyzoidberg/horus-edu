#ifndef TOOLS_H
#define TOOLS_H
#include "../../../../../Common/TreeData.h"
#include "../../../../../Common/UserData.h"

class mytools
{
private:
    TreeDataPlugin *_treeplugin;
    UserDataPlugin *_userplugin;
public:
    mytools(TreeDataPlugin *_mtreeplugin, UserDataPlugin *_muserplugin);
    QMap<int, QString> getallclass(TreeDataPlugin *treeplugin);
    QList<UserData*> getStudentfromClass(int id);
};

#endif // TOOLS_H
