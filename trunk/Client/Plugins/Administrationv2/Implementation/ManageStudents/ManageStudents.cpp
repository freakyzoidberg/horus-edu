#include "ManageStudents.h"
#include <QDebug>
#include <QMessageBox>

ManageStudents::ManageStudents(TreeDataPlugin *treeplugin, UserDataPlugin *userplugin)
{
    UD = userplugin;
    TD = treeplugin;
    info = 0;
    MainLayout = new QHBoxLayout();
    MainLayout->setSpacing(0);
    MainLayout->setMargin(2);

    QVBoxLayout *RightLayout = new QVBoxLayout();

    StudentList = new ListSelection(treeplugin, userplugin);
    addstudent = new QPushButton(QIcon(":/Icons/add-students.png"), tr("Add a student"));
    del = new QPushButton(QIcon(":/Icons/remove-students.png"), tr("Delete this student"));
    edit = new QPushButton(QIcon(":/Icons/edit-students.png"), tr("Edit this student"));
    ok = new QPushButton(QIcon(":/Icons/ok.png"), tr("Ok"));
    save = new QPushButton(QIcon(":/Icons/save.png"), tr("Apply"));
    reset = new QPushButton(QIcon(":/Icons/reset.png"), tr("Reset"));
    back = new QPushButton(QIcon(":/Icons/back.png"), tr("Cancel"));
    StudentForm = 0;

    connect(addstudent, SIGNAL(clicked()), this, SLOT(goadd()));
    connect(edit, SIGNAL(clicked()), this, SLOT(goedit()));
    connect(back, SIGNAL(clicked()), this, SLOT(goback()));
    connect(reset, SIGNAL(clicked()), this, SLOT(goreset()));
    connect(del, SIGNAL(clicked()), this, SLOT(godel()));
    connect(StudentList->ClassList, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(seteditfalse()));
    connect(StudentList->StudentList, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(setedittrue()));
    connect(UD, SIGNAL(dataCreated(Data*)), this, SLOT(checkCreated(Data*)));

    RightLayout->setMargin(0);
    RightLayout->setSpacing(2);
    QLabel *infoTitle = new QLabel(tr("Informations:"));
    infoTitle->setProperty("isTitle", true);
    infoTitle->setProperty("isRound", true);
    informationsFrame = new QFrame(this);
    informationsFrame->setMinimumWidth(200);
    informationsLayout = new QVBoxLayout(informationsFrame);
    informationsLayout->setSpacing(0);
    informationsLayout->setMargin(0);
    informationsLayout->addWidget(infoTitle);
    RightLayout->addWidget(informationsFrame);

    QLabel *actionTitle = new QLabel(tr("Actions:"));
    actionTitle->setProperty("isTitle", true);
    actionTitle->setProperty("isRound", true);
    RightLayout->addWidget(actionTitle);
    RightLayout->addWidget(addstudent);
    RightLayout->addWidget(edit);
    RightLayout->addWidget(del);
    RightLayout->addWidget(ok);
    RightLayout->addWidget(save);
    RightLayout->addWidget(reset);
    RightLayout->addWidget(back);
    RightLayout->addWidget(new QWidget(this), 1);

    MainLayout->addWidget(StudentList);
    //MainLayout->addLayout(ActionLayout);


    MainLayout->addLayout(RightLayout);





	ok->setVisible(false);
    save->setVisible(false);
	reset->setVisible(false);
    back->setVisible(false);
    edit->setVisible(true);
    del->setVisible(true);
    edit->setEnabled(false);
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
        StudentForm = new FormStudents(getAllParents());
        MainLayout->insertWidget(0, StudentForm);
        connect(ok, SIGNAL(clicked()), this, SLOT(gook()));
        connect(save, SIGNAL(clicked()), this, SLOT(gosave()));
        StudentList->setVisible(false);


		ok->setVisible(true);
        save->setVisible(true);
		reset->setVisible(true);
        back->setVisible(true);
        addstudent->setVisible(false);
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
    StudentForm = new FormStudents(getAllParents(),UD->parentsOfStudent(UD->user(StudentList->StudentList->selectedItems().first()->data(Qt::UserRole).toInt())), UD->user(StudentList->StudentList->selectedItems().first()->data(Qt::UserRole).toInt()));
    MainLayout->insertWidget(0, StudentForm);
    connect(ok, SIGNAL(clicked()), this, SLOT(gook()));
    connect(save, SIGNAL(clicked()), this, SLOT(gosave()));
    StudentList->setVisible(false);

	ok->setVisible(true);
    save->setVisible(true);    
	reset->setVisible(true);
    back->setVisible(true);
    addstudent->setVisible(false);
    edit->setVisible(false);
    del->setVisible(false);


}



void ManageStudents::godel()
{

    if (StudentList->StudentList->selectedItems().count() > 0)
    {
        UserData* myuser = UD->user(StudentList->StudentList->selectedItems().first()->data(Qt::UserRole).toInt());
        myuser->remove();
StudentList->updatestudents(StudentList->ClassList->selectedItems().first());
if (info)
{
delete info;
info = 0;
}    }

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
	ok->setVisible(false);
    save->setVisible(false);
	reset->setVisible(false);
    back->setVisible(false);



    if (StudentList->StudentList->selectedItems().count() > 0)
    {

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

            // Referenr +"|:/:|:/|"+ aides +"|:/:|:/|"+  raisons redoublement
            newUSer->setComment(StudentForm->SocInfos->getReferent()+"|:/:|:/|"+StudentForm->SocInfos->getAides()+"|:/:|:/|"+StudentForm->SchoInfos->getRaison()+"|:/:|:/|");

            newUSer->setMail("test debug");
            //Scholar infos
            newUSer->setRepeatedYears(StudentForm->SchoInfos->getNb_red());

            //Parent
            //newUSer->setRelationship(QVariant(x).toString());
            //Suivi infos





            newUSer->setFollowUp(StudentForm->SuiInfos->getSuivi());
            newUSer->setLeaveYear(StudentForm->SuiInfos->getLeftYear());
                //ClasseNextYear


            newUSer->setEnable(true);
            if (StudentForm->id == 0)
                newUSer->create();
            else
                newUSer->save();


            UserData *uparent = UD->user(UD->user(StudentForm->ParInfos->getParent()->itemData(StudentForm->ParInfos->getParent()->currentIndex(), Qt::UserRole).toInt())->id());
            if (uparent != 0)
            {
                uparent->setStudent(newUSer);
                uparent->save();
            }


   //         delete StudentForm;
   //         StudentForm = 0;
   //         edit->setVisible(true);
   //         addstudent->setVisible(true);
   //         save->setVisible(false);
   //         StudentList->setVisible(true);
   //         StudentList->updatestudents(StudentList->ClassList->selectedItems().first());
   //         addstudent->setVisible(true);
			//ok->setVisible(false);
   //         save->setVisible(false);
			//reset->setVisible(false);
   //         back->setVisible(false);
   //         edit->setVisible(true);
   //         edit->setEnabled(false);
   //         del->setVisible(true);
   //         edit->setEnabled(false);

        }
   // if (info)
   //     {
   // delete info;
   // info = 0;
   //     }
    }
}
void ManageStudents::goreset()
{
}
void ManageStudents::gook()
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

            // Referenr +"|:/:|:/|"+ aides +"|:/:|:/|"+  raisons redoublement
            newUSer->setComment(StudentForm->SocInfos->getReferent()+"|:/:|:/|"+StudentForm->SocInfos->getAides()+"|:/:|:/|"+StudentForm->SchoInfos->getRaison()+"|:/:|:/|");

            newUSer->setMail("test debug");
            //Scholar infos
            newUSer->setRepeatedYears(StudentForm->SchoInfos->getNb_red());

            //Parent
            //newUSer->setRelationship(QVariant(x).toString());
            //Suivi infos





            newUSer->setFollowUp(StudentForm->SuiInfos->getSuivi());
            newUSer->setLeaveYear(StudentForm->SuiInfos->getLeftYear());
                //ClasseNextYear


            newUSer->setEnable(true);
            if (StudentForm->id == 0)
                newUSer->create();
            else
                newUSer->save();


            UserData *uparent = UD->user(UD->user(StudentForm->ParInfos->getParent()->itemData(StudentForm->ParInfos->getParent()->currentIndex(), Qt::UserRole).toInt())->id());
            if (uparent != 0)
            {
                uparent->setStudent(newUSer);
                uparent->save();
            }


            delete StudentForm;
            StudentForm = 0;
            edit->setVisible(true);
            addstudent->setVisible(true);
            save->setVisible(false);
            StudentList->setVisible(true);
            StudentList->updatestudents(StudentList->ClassList->selectedItems().first());
            addstudent->setVisible(true);
			ok->setVisible(false);
            save->setVisible(false);
			reset->setVisible(false);
            back->setVisible(false);
            edit->setVisible(true);
            edit->setEnabled(false);
            del->setVisible(true);
            del->setEnabled(false);

        }
    if (info)
        {
    delete info;
    info = 0;
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
    if (info)
    {
        delete info;
        info = 0;
    }
     edit->setEnabled(false);
     del->setEnabled(false);
}

void ManageStudents::setedittrue()
{
     edit->setEnabled(true);
     del->setEnabled(true);
    if (info)
     {
        delete info;
        info = 0;
    }
    info = new InfoPanel(UD->user(StudentList->StudentList->selectedItems().first()->data(Qt::UserRole).toInt()));
    informationsLayout->addWidget(info);
}


QList<UserData*> ManageStudents::getAllParents()
{
    QList<UserData*> mylist;

    foreach (UserData* user, UD->allUser())
    {
        qDebug() <<user->id()<< " -----: " << user->level();
        if (user->level() == LEVEL_FAMILY)
        {
            mylist.append(user);
        }
    }
    return mylist;
}
