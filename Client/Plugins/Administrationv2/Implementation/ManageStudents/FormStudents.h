#ifndef FORMSTUDENTS_H
#define FORMSTUDENTS_H

#include <QWidget>

#include <QVBoxLayout>
#include "../../../../../Common/UserData.h"
#include "BasicInfos.h"
#include "Socialinfos.h"
#include "Schoolinfos.h"
#include "Suiviinfos.h"
class FormStudents : public QWidget
{
public:
    FormStudents();
    FormStudents(UserData *user);
    BasicInfos *BaseInfos;
    SocialInfos *SocInfos;
    SchoolInfos *SchoInfos;
    SuiviInfos *SuiInfos;
    int id;
};

#endif // FORMSTUDENTS_H
