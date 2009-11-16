#include "ManageStudents.h"
#include <QDebug>
#include <QMessageBox>
ManageStudents::ManageStudents(TreeDataPlugin *treeplugin, UserDataPlugin *userplugin)
{
    UD = userplugin;

    MainLayout = new QHBoxLayout();

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
    connect(StudentList->ClassList, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(seteditfalse()));
    connect(StudentList->StudentList, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(setedittrue()));
    ActionLayout->addWidget(back);
    ActionLayout->addWidget(save);
    ActionLayout->addWidget(edit);
    ActionLayout->addWidget(addstudent);

    MainLayout->addWidget(StudentList);
    //MainLayout->addLayout(ActionLayout);




    QBoxLayout	*rightLayout;
    rightLayout = new  QBoxLayout(QBoxLayout::TopToBottom);
    QFrame *informationsFrame = new QFrame(this);
    informationsFrame->setMinimumWidth(200);
    QBoxLayout *informationsLayout = new QBoxLayout(QBoxLayout::TopToBottom, informationsFrame);
    QLabel *informationsTitle = new QLabel(this);
    informationsLayout->addWidget(informationsTitle);
    //informationsLayout->addWidget(new DisplayParent(this));
    rightLayout->addWidget(informationsFrame);
    rightLayout->addLayout(ActionLayout);
    MainLayout->addLayout(rightLayout);





    save->setVisible(false);
    back->setVisible(false);
    edit->setVisible(false);

    StudentList->updateall();



    this->setLayout(MainLayout);
}


void ManageStudents::goadd()
{
    if (StudentList->ClassList->selectedItems().count() == 1)
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
    else
       qDebug() << "Erreur";
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
        if (!StudentForm->BaseInfos->getName().isEmpty() &&
            !StudentForm->BaseInfos->getSurName().isEmpty() &&
            !StudentForm->BaseInfos->getBday().isEmpty())
        {


            UserData* newUSer = UD->createUser(StudentForm->BaseInfos->getName());

            newUSer->setAddress(StudentForm->BaseInfos->getAddress());
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
}

void ManageStudents::seteditfalse()
{
     edit->setVisible(false);
}

void ManageStudents::setedittrue()
{
     edit->setVisible(true);
}
