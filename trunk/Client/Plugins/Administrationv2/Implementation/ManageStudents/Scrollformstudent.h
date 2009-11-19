#ifndef SCROLLFORMSTUDENT_H
#define SCROLLFORMSTUDENT_H
#include <QScrollArea>
#include "FormStudents.h"
class ScrollFormStudent : public QScrollArea
{
public:
    ScrollFormStudent(QList<UserData*> list, int idnode);
    FormStudents *StudentForm;
    ScrollFormStudent(QList<UserData*> list, QList<UserData*> parentlist,UserData *d, int idnode);
    ~ScrollFormStudent();
    int getnodeid() {return _nodeid;}
private:
    int _nodeid;
};

#endif // SCROLLFORMSTUDENT_H
