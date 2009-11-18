#ifndef FORMSTUDENTS_H
#define FORMSTUDENTS_H

#include <QWidget>

#include <QVBoxLayout>
#include "../../../../../Common/UserData.h"
#include "BasicInfos.h"
#include "Socialinfos.h"
#include "Schoolinfos.h"
#include "Suiviinfos.h"
#include "Parentinfos.h"
class FormStudents : public QWidget
{
public:
    FormStudents(QList<UserData*> list);
    FormStudents(QList<UserData*> list, QList<UserData*> parentlist,UserData *user);
    BasicInfos *BaseInfos;
    SocialInfos *SocInfos;
    SchoolInfos *SchoInfos;
    SuiviInfos *SuiInfos;
    ParentInfos *ParInfos;
    int id;
};

#endif // FORMSTUDENTS_H