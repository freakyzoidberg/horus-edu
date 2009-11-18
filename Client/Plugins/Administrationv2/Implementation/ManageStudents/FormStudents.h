#ifndef FORMSTUDENTS_H
#define FORMSTUDENTS_H

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include "../../../../../Common/UserData.h"
#include "BasicInfos.h"
#include "Socialinfos.h"
#include "Schoolinfos.h"
#include "Suiviinfos.h"
#include "Parentinfos.h"
#include "../ManageParents/EditParent.h"

class FormStudents : public QWidget
{
public:
    FormStudents(QList<UserData*> list);
    FormStudents(QList<UserData*> list, QList<UserData*> parentlist,UserData *user);
    BasicInfos *BaseInfos;
    SocialInfos *SocInfos;
    SchoolInfos *SchoInfos;
    SuiviInfos *SuiInfos;
    //ParentInfos *ParInfos;
    EditParent *ParInfos;
    int id;
};

#endif // FORMSTUDENTS_H
