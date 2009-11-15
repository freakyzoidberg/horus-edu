#include "ManageStudents.h"
#include <QDebug>
ManageStudents::ManageStudents(TreeDataPlugin *treeplugin, UserDataPlugin *userplugin)
{


    MainLayout = new QVBoxLayout();
    QHBoxLayout *ActionLayout = new QHBoxLayout();

    StudentList = new ListSelection(treeplugin, userplugin);
    addstudent = new QPushButton(tr("add"));
    back = new QPushButton(tr("back"));
    edit = new QPushButton(tr("edit"));
    save = new QPushButton(tr("save"));
    StudentForm = 0;




    connect(addstudent, SIGNAL(clicked()), this, SLOT(goadd()));
    connect(edit, SIGNAL(clicked()), this, SLOT(goedit()));
    connect(back, SIGNAL(clicked()), this, SLOT(goback()));

    ActionLayout->addWidget(back);
    ActionLayout->addWidget(save);
    ActionLayout->addWidget(edit);
    ActionLayout->addWidget(addstudent);

    MainLayout->addWidget(StudentList);
    MainLayout->addLayout(ActionLayout);

    save->setVisible(false);
    back->setVisible(false);

    StudentList->updateall();
    this->setLayout(MainLayout);
}


void ManageStudents::goadd()
{
if (StudentForm)
    {
        delete StudentForm;
        StudentForm = 0;
    }
    StudentForm = new FormStudents();
    MainLayout->insertWidget(0, StudentForm);
    connect(save, SIGNAL(clicked()), this, SLOT(gosave()));
    StudentList->setVisible(false);



    addstudent->setVisible(false);
    save->setVisible(true);
    back->setVisible(true);

    edit->setVisible(false);

}

void ManageStudents::goedit()
{

if (StudentForm)
    {
        delete StudentForm;
        StudentForm = 0;
    }
    StudentForm = new FormStudents();
    MainLayout->insertWidget(0, StudentForm);
    connect(save, SIGNAL(clicked()), this, SLOT(gosave()));
    StudentList->setVisible(false);

    addstudent->setVisible(false);
    save->setVisible(true);    
    back->setVisible(true);

    edit->setVisible(false);
}

void ManageStudents::goback()
{
if (StudentForm)
    {
        delete StudentForm;
        StudentForm = 0;
        StudentList->setVisible(true);
        edit->setVisible(true);
        addstudent->setVisible(true);
        save->setVisible(false);
    }
    addstudent->setVisible(true);
    save->setVisible(false);
    back->setVisible(false);

    edit->setVisible(true);
}

void ManageStudents::gosave()
{
if (StudentForm)
    {
        delete StudentForm;
        StudentForm = 0;
        edit->setVisible(true);
        addstudent->setVisible(true);
        save->setVisible(false);
        StudentList->setVisible(true);

        addstudent->setVisible(true);
        save->setVisible(false);
        back->setVisible(false);

        edit->setVisible(true);

    }
}
