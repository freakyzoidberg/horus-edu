#include "Scrollformstudent.h"

ScrollFormStudent::ScrollFormStudent(QList<UserData*> list, int idnode)
{
    StudentForm = 0;
    _nodeid = idnode;
    StudentForm = new FormStudents(list);

    this->setWidget(StudentForm);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setWidgetResizable(true);

}

ScrollFormStudent::ScrollFormStudent(QList<UserData*> list, QList<UserData*> parentlist,UserData *d, int idnode)
{
    StudentForm = 0;
    _nodeid = idnode;
    StudentForm = new FormStudents(list,parentlist, d);

    this->setWidget(StudentForm);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setWidgetResizable(true);
}


ScrollFormStudent::~ScrollFormStudent()
{
    if (StudentForm)
    {
        delete StudentForm;

    }

}
