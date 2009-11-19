#include "Scrollformstudent.h"

ScrollFormStudent::ScrollFormStudent(QList<UserData*> list)
{
    StudentForm = 0;
    StudentForm = new FormStudents(list);

    this->setWidget(StudentForm);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setWidgetResizable(true);

}

ScrollFormStudent::ScrollFormStudent(QList<UserData*> list, QList<UserData*> parentlist,UserData *d)
{
    StudentForm = 0;
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
