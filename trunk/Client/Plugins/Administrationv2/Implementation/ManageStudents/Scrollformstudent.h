#ifndef SCROLLFORMSTUDENT_H
#define SCROLLFORMSTUDENT_H
#include <QScrollArea>
#include "FormStudents.h"
class ScrollFormStudent : public QScrollArea
{
public:
    ScrollFormStudent(QList<UserData*> list);
    FormStudents *StudentForm;
    ScrollFormStudent(QList<UserData*> list, QList<UserData*> parentlist,UserData *d);
    ~ScrollFormStudent();
};

#endif // SCROLLFORMSTUDENT_H
