#include "ManageStudents.h"
#include <QDebug>
#include <QMessageBox>
ManageStudents::ManageStudents(TreeDataPlugin *treeplugin, UserDataPlugin *userplugin)
{
    UD = userplugin;
    TD = treeplugin;

    MainLayout = new QHBoxLayout();

    QHBoxLayout *ActionLayout = new QHBoxLayout();

    StudentList = new ListSelection(treeplugin, userplugin);
    addstudent = new QPushButton(tr("add"));
    back = new QPushButton(tr("back"));
    edit = new QPushButton(tr("edit"));
    save = new QPushButton(tr("save"));
    del = new QPushButton(tr("delete"));
    StudentForm = 0;




    connect(addstudent, SIGNAL(clicked()), this, SLOT(goadd()));
    connect(edit, SIGNAL(clicked()), this, SLOT(goedit()));
    connect(back, SIGNAL(clicked()), this, SLOT(goback()));
    connect(del, SIGNAL(clicked()), this, SLOT(godel()));
    connect(StudentList->ClassList, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(seteditfalse()));
    connect(StudentList->StudentList, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(setedittrue()));
    connect(UD, SIGNAL(dataCreated(Data*)), this, SLOT(checkCreated(Data*)));
    ActionLayout->addWidget(back);
    ActionLayout->addWidget(save);
    ActionLayout->addWidget(edit);
    ActionLayout->addWidget(del);
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
    edit->setVisible(true);
    edit->setEnabled(false);
    del->setVisible(true);
    del->setEnabled(false);
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
        del->setVisible(false);
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
StudentForm = new FormStudents(UD->user(StudentList->StudentList->selectedItems().first()->data(Qt::UserRole).toInt()));
    MainLayout->insertWidget(0, StudentForm);
    connect(save, SIGNAL(clicked()), this, SLOT(gosave()));
    StudentList->setVisible(false);

    addstudent->setVisible(false);
    save->setVisible(true);    
    back->setVisible(true);
    edit->setVisible(false);
    del->setVisible(false);
}



void ManageStudents::godel()
{
    qDebug() << "del from " <<  StudentList->ClassList->selectedItems().first()->data(Qt::UserRole);
    if (StudentList->StudentList->selectedItems().count() > 0)
    {
        UserData* myuser = UD->user(StudentList->StudentList->selectedItems().first()->data(Qt::UserRole).toInt());
        myuser->remove();
StudentList->updatestudents(StudentList->ClassList->selectedItems().first());
    }

}







void ManageStudents::goback()
{
    if (StudentForm)
    {
        delete StudentForm;
        StudentForm = 0;
        StudentList->setVisible(true);

        addstudent->setVisible(true);
        save->setVisible(false);
    }
    addstudent->setVisible(true);
    save->setVisible(false);
    back->setVisible(false);



    if (StudentList->StudentList->selectedItems().count() > 0)
    {
        qDebug() << "count : " << StudentList->StudentList->selectedItems().count();
    del->setEnabled(true);
    edit->setEnabled(true);
    }
    else
    {
        del->setEnabled(false);
        edit->setEnabled(false);
    }
    del->setVisible(true);
    edit->setVisible(true);
}

void ManageStudents::gosave()
{
    if (StudentForm)
    {

        if (!StudentForm->BaseInfos->getName().isEmpty() &&
            !StudentForm->BaseInfos->getSurName().isEmpty())
        {


          //  qDebug() << StudentList->ClassList->selectedItems().first()->data(Qt::UserRole);

//qDebug() << "id user" << StudentForm->id;

            UserData* newUSer;
            if (StudentForm->id == 0)
            newUSer = UD->createUser(StudentForm->BaseInfos->getName());
            else
            newUSer = UD->user(StudentForm->id);


            //Data
            newUSer->setName(StudentForm->BaseInfos->getName());
            newUSer->setLevel(LEVEL_STUDENT);
            newUSer->setStudentClass(TD->node(StudentList->ClassList->selectedItems().first()->data(Qt::UserRole).toInt()));
            newUSer->setPassword(StudentForm->BaseInfos->getSurName());
            //BasicInfos
            newUSer->setSurname(StudentForm->BaseInfos->getSurName());
            newUSer->setAddress(StudentForm->BaseInfos->getAddress());
            newUSer->setBirthDate(StudentForm->BaseInfos->getBday());


            //Social Infos
            newUSer->setSubscriptionReason(StudentForm->SocInfos->getMotif());
            qDebug() << "Motif " << StudentForm->SocInfos->getMotif();
            // Referenr +"|:/:|:/|"+ aides +"|:/:|:/|"+  raisons redoublement
            newUSer->setComment(StudentForm->SocInfos->getReferent()+"|:/:|:/|"+StudentForm->SocInfos->getAides()+"|:/:|:/|"+StudentForm->SchoInfos->getRaison());


            //Scholar infos
            newUSer->setRepeatedYears(StudentForm->SchoInfos->getNb_red());



            //Suivi infos
            newUSer->setFollowUp(StudentForm->SuiInfos->getSuivi());
            newUSer->setLeaveYear(StudentForm->SuiInfos->getLeftYear());
                //ClasseNextYear


            newUSer->setEnable(true);
            if (StudentForm->id == 0)
                newUSer->create();
            else
                newUSer->save();
            delete StudentForm;
            StudentForm = 0;
            edit->setVisible(true);
            addstudent->setVisible(true);
            save->setVisible(false);
            StudentList->setVisible(true);
            StudentList->updatestudents(StudentList->ClassList->selectedItems().first());
            addstudent->setVisible(true);
            save->setVisible(false);
            back->setVisible(false);
            edit->setVisible(true);
            edit->setEnabled(false);
            del->setVisible(true);
            edit->setEnabled(false);

        }

    }
}

void ManageStudents::checkCreated(Data *user)
{
   // QMessageBox msgBox;
   // msgBox.setText(tr("L'utilisateur a bien ete crée"));
   // msgBox.exec();
}

void ManageStudents::seteditfalse()
{
     edit->setEnabled(false);
     del->setEnabled(false);
}

void ManageStudents::setedittrue()
{
     edit->setEnabled(true);
     del->setEnabled(true);
}
