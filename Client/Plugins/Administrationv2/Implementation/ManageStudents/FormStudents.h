#ifndef FORMSTUDENTS_H
#define FORMSTUDENTS_H

#include <QWidget>
#include "BasicInfos.h"
#include <QVBoxLayout>
#include "../../../../../Common/UserData.h"
class FormStudents : public QWidget
{
public:
    FormStudents();
    FormStudents(UserData *user);
};

#endif // FORMSTUDENTS_H
