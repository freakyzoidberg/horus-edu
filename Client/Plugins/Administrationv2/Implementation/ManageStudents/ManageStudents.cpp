#include "ManageStudents.h"
#include <QDebug>
#include <QMessageBox>

ManageStudents::ManageStudents(TreeDataPlugin *treeplugin, UserDataPlugin *userplugin)
{
    UD = userplugin;
    TD = treeplugin;
    newUSer = 0;
    newPapa = 0;
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
    back = new QPushButton(QIcon(":/Icons/back.png"), tr("Cancel"));

    //StudentForm = 0;
    scrollStudentForm = 0;

    connect(addstudent, SIGNAL(clicked()), this, SLOT(goadd()));
    connect(edit, SIGNAL(clicked()), this, SLOT(goedit()));
    connect(back, SIGNAL(clicked()), this, SLOT(goback()));
    connect(reset, SIGNAL(clicked()), this, SLOT(goreset()));
    connect(del, SIGNAL(clicked()), this, SLOT(godel()));
    connect(StudentList->ClassList, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(seteditfalse()));
    connect(StudentList->StudentList, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(setedittrue()));

    //connect(UD, SIGNAL(dataCreated(Data*)), this, SLOT(checkCreated(Data*)));
    connect(save, SIGNAL(clicked()), this, SLOT(gosave()));
    connect(ok, SIGNAL(clicked()), this, SLOT(gook()));

        connect(UD, SIGNAL(dataCreated(Data *)), StudentList, SLOT(updatestudents()));
        connect(UD, SIGNAL(dataUpdated(Data *)), StudentList, SLOT(updatestudents()));
        connect(UD, SIGNAL(dataRemoved(Data *)), StudentList, SLOT(updatestudents()));

        connect(treeplugin, SIGNAL(dataCreated(Data *)), this, SLOT(refreshall()));
        connect(treeplugin, SIGNAL(dataUpdated(Data *)), this, SLOT(refreshall()));
        connect(treeplugin, SIGNAL(dataRemoved(Data *)), this, SLOT(refreshall()));

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
    if (scrollStudentForm)
        {
            delete scrollStudentForm;
            scrollStudentForm = 0;
        }
    scrollStudentForm = new ScrollFormStudent(getAllParents(), StudentList->ClassList->selectedItems().first()->data(Qt::UserRole).toInt());
        MainLayout->insertWidget(0, scrollStudentForm);
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

    if (scrollStudentForm)
        {
            delete scrollStudentForm;
            scrollStudentForm = 0;
        }

    if ((StudentList->StudentList->selectedItems().count() == 1) &&  (StudentList->ClassList->selectedItems().count() > 0))
    {
    scrollStudentForm = new ScrollFormStudent(getAllParents(),UD->parentsOfStudent(UD->user(StudentList->StudentList->selectedItems().first()->data(Qt::UserRole).toInt())), UD->user(StudentList->StudentList->selectedItems().first()->data(Qt::UserRole).toInt()), StudentList->ClassList->selectedItems().first()->data(Qt::UserRole).toInt());
    MainLayout->insertWidget(0, scrollStudentForm);
    StudentList->setVisible(false);
    ok->setVisible(true);
    save->setVisible(true);    
    reset->setVisible(true);
    back->setVisible(true);
    addstudent->setVisible(false);
    edit->setVisible(false);
    del->setVisible(false);
    }

}



void ManageStudents::godel()
{

    if (StudentList->StudentList->selectedItems().count() > 0)
    {
        UserData* myuser = UD->user(StudentList->StudentList->selectedItems().first()->data(Qt::UserRole).toInt());
        myuser->remove();
        if (StudentList->ClassList->selectedItems().count() > 0)
            StudentList->updatestudents(StudentList->ClassList->selectedItems().first());
        if (info)
        {
            delete info;
            info = 0;
        }
    }

}







void ManageStudents::goback()
{

    if (scrollStudentForm)
        {
            delete scrollStudentForm;
            scrollStudentForm = 0;
            StudentList->setVisible(true);

            addstudent->setVisible(true);
            save->setVisible(false);
        }



    addstudent->setVisible(true);
	ok->setVisible(false);
    save->setVisible(false);
	reset->setVisible(false);
    back->setVisible(false);


   if (StudentList->ClassList->selectedItems().count() > 0)
    {
    StudentList->updatestudents(StudentList->ClassList->selectedItems().first());
   }
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

 if ((scrollStudentForm) &&  (scrollStudentForm->StudentForm))
    {
        if (!scrollStudentForm->StudentForm->BaseInfos->getName().isEmpty() &&
            !scrollStudentForm->StudentForm->BaseInfos->getSurName().isEmpty())
        {
            if (scrollStudentForm->StudentForm->id == 0)
            {
                newUSer = UD->createUser(scrollStudentForm->StudentForm->BaseInfos->getName());
                newPapa = UD->createUser(scrollStudentForm->StudentForm->ParInfos->getlastN());
                connect(newUSer, SIGNAL(created()), newPapa, SLOT(create()));
                connect(newPapa, SIGNAL(created()), this, SLOT(userCreated(Data*)));
            }
            else
            {
                newUSer = UD->user(scrollStudentForm->StudentForm->id);

                if (UD->parentsOfStudent(newUSer).count() > 0)
                newPapa = UD->parentsOfStudent(newUSer)[0];
                else
                   newPapa = UD->createUser(scrollStudentForm->StudentForm->ParInfos->getlastN());

                if ((newUSer->status() != Data::UPTODATE) &&
                    (newUSer->status() != Data::UPDATED) &&
                    (newUSer->status() != Data::SAVED) &&
                    (newUSer->status() != Data::CREATED) )
                {
                       QMessageBox msgBox;
                       msgBox.setText(tr("Saving failed, please try later sur id :")+ QVariant(StudentForm->id).toString());
                       msgBox.exec();
                       return;
                }
            newUSer = UD->user(scrollStudentForm->StudentForm->id);

            }
            //Data
            newUSer->setName(scrollStudentForm->StudentForm->BaseInfos->getName());
            newUSer->setLevel(LEVEL_STUDENT);
            newUSer->setStudentClass(TD->node(scrollStudentForm->getnodeid()));
            newUSer->setPassword(scrollStudentForm->StudentForm->BaseInfos->getSurName());
            //BasicInfos
            newUSer->setSurname(scrollStudentForm->StudentForm->BaseInfos->getSurName());
            newUSer->setAddress(scrollStudentForm->StudentForm->BaseInfos->getAddress());
            newUSer->setBirthDate(scrollStudentForm->StudentForm->BaseInfos->getBday());


            //Social Infos
            newUSer->setSubscriptionReason(scrollStudentForm->StudentForm->SocInfos->getMotif());

            // Referenr +"|:/:|:/|"+ aides +"|:/:|:/|"+  raisons redoublement
            newUSer->setComment(scrollStudentForm->StudentForm->SocInfos->getReferent()+"|:/:|:/|"+scrollStudentForm->StudentForm->SocInfos->getAides()+"|:/:|:/|");

            newUSer->setMail("test debug");
            //Scholar infos
            newUSer->setRepeatedYears(scrollStudentForm->StudentForm->SchoInfos->getNb_red());

            //Parents info




            //newUSer->setRelationship(QVariant(x).toString());
            //Suivi infos





            newUSer->setFollowUp(scrollStudentForm->StudentForm->SuiInfos->getSuivi());
            newUSer->setLeaveYear(scrollStudentForm->StudentForm->SuiInfos->getLeftYear());
                //ClasseNextYear


            newUSer->setEnable(true);

            if (scrollStudentForm->StudentForm->id == 0)
            {
                newUSer->create();
                scrollStudentForm->StudentForm->id = newUSer->id();
            }
            else
                newUSer->save();
//***ParInfo
//            UserData *uparent = UD->user(UD->user(StudentForm->ParInfos->getParent()->itemData(StudentForm->ParInfos->getParent()->currentIndex(), Qt::UserRole).toInt())->id());
//            if (uparent != 0)
//            {
//                uparent->setStudent(newUSer);
//                uparent->save();
//            }

/* On detruis pas sur le apply
            if (scrollStudentForm)
                {
                    delete scrollStudentForm;
                    scrollStudentForm = 0;
                }


            scrollStudentForm = new ScrollFormStudent(getAllParents());
            MainLayout->insertWidget(0, scrollStudentForm);
*/
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
    if ((scrollStudentForm) &&  (scrollStudentForm->StudentForm))
    {

        if (!scrollStudentForm->StudentForm->BaseInfos->getName().isEmpty() &&
            !scrollStudentForm->StudentForm->BaseInfos->getSurName().isEmpty())
        {


          //  qDebug() << StudentList->ClassList->selectedItems().first()->data(Qt::UserRole);

//qDebug() << "id user" << StudentForm->id;

//            UserData* newUSer;
//            UserData* newPapa;
            if (scrollStudentForm->StudentForm->id == 0)
            {
                newUSer = UD->createUser(scrollStudentForm->StudentForm->BaseInfos->getName());
                newPapa = UD->createUser(scrollStudentForm->StudentForm->ParInfos->getlastN());
                connect(newUSer, SIGNAL(created()), newPapa, SLOT(create()));

                // tu ne peux pas linker un signal sans parametre a un slot avec parametre
                //connect(newPapa, SIGNAL(created()), this, SLOT(userCreated(Data*)));
            }
            else
            {
                newUSer = UD->user(scrollStudentForm->StudentForm->id);
                if (UD->parentsOfStudent(newUSer).count() > 0)
                newPapa = UD->parentsOfStudent(newUSer)[0];
                else
                   newPapa = UD->createUser(scrollStudentForm->StudentForm->ParInfos->getlastN());
            }


            //newUSer = UD->user(scrollStudentForm->StudentForm->id);


            //Data
            newUSer->setName(scrollStudentForm->StudentForm->BaseInfos->getName());
            newUSer->setLevel(LEVEL_STUDENT);
            newUSer->setStudentClass(TD->node(StudentList->ClassList->selectedItems().first()->data(Qt::UserRole).toInt()));
            newUSer->setPassword(scrollStudentForm->StudentForm->BaseInfos->getSurName());
            //BasicInfos
            newUSer->setSurname(scrollStudentForm->StudentForm->BaseInfos->getSurName());
            newUSer->setAddress(scrollStudentForm->StudentForm->BaseInfos->getAddress());
            newUSer->setBirthDate(scrollStudentForm->StudentForm->BaseInfos->getBday());


            //Social Infos
            newUSer->setSubscriptionReason(scrollStudentForm->StudentForm->SocInfos->getMotif());

            // Referenr +"|:/:|:/|"+ aides +"|:/:|:/|"+  raisons redoublement
            newUSer->setComment(scrollStudentForm->StudentForm->SocInfos->getReferent()+"|:/:|:/|"+scrollStudentForm->StudentForm->SocInfos->getAides()+"|:/:|:/|");

            newUSer->setMail("test debug");
            //Scholar infos
            newUSer->setRepeatedYears(scrollStudentForm->StudentForm->SchoInfos->getNb_red());

            //Parent's Infos

            newPapa->setLevel(LEVEL_FAMILY);
            newPapa->setAddress(scrollStudentForm->StudentForm->ParInfos->getaddr());
            newPapa->setSurname(scrollStudentForm->StudentForm->ParInfos->getfirsN());
            newPapa->setAddress(scrollStudentForm->StudentForm->ParInfos->getaddr());
            newPapa->setAddress(scrollStudentForm->StudentForm->ParInfos->getaddr());
            newPapa->setAddress(scrollStudentForm->StudentForm->ParInfos->getaddr());
            newPapa->setAddress(scrollStudentForm->StudentForm->ParInfos->getaddr());
            newPapa->setAddress(scrollStudentForm->StudentForm->ParInfos->getaddr());

//            _user->setEnable(true);
//            _user->setName(lastNameField->text());
//            _user->setSurname(firstNameField->text());
//            _user->setGender(static_cast<UserGender>(genderField->itemData(genderField->currentIndex()).toInt()));
//            _user->setBirthDate(birthDateField->date());
//            _user->setRelationship(relationshipField->itemData(relationshipField->currentIndex()).toString());
//            _user->setAddress(addressField->document()->toPlainText());
//            _user->setMail(mailField->text());
//            _user->setPhone1(homePhoneField->text());
//            _user->setPhone2(workPhoneField->text());
//            _user->setPhone3(mobilePhoneField->text());
//            _user->setOccupation(occupationField->text());
//            _user->setProCategory(occupationalCategoryField->text());
//            _user->setLevel(LEVEL_FAMILY);

            //Suivi infos





            newUSer->setFollowUp(scrollStudentForm->StudentForm->SuiInfos->getSuivi());
            newUSer->setLeaveYear(scrollStudentForm->StudentForm->SuiInfos->getLeftYear());
                //ClasseNextYear


   // connect(UD, dataUpdated(newUSer), StudentList->updatestudents(StudentList->ClassList->selectedItems().first()));
            newUSer->setEnable(true);
            if (scrollStudentForm->StudentForm->id == 0)
                newUSer->create();
            else
                newUSer->save();

//***ParInfo
//            UserData *uparent = UD->user(UD->user(StudentForm->ParInfos->getParent()->itemData(StudentForm->ParInfos->getParent()->currentIndex(), Qt::UserRole).toInt())->id());
//            if (uparent)
//            {
//                if (uparent->name() != "Nobody")
//                {
//                uparent->setStudent(newUSer);
//                uparent->save();
//                }
//            }


            delete scrollStudentForm;
            scrollStudentForm = 0;
            edit->setVisible(true);
            addstudent->setVisible(true);
            save->setVisible(false);
            StudentList->setVisible(true);
            if (StudentList->ClassList->selectedItems().count() > 0)
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

void ManageStudents::userCreated(Data *)
{
    disconnect(this, SLOT(userCreated(Data*)));
    newPapa->setStudent(newUSer);
    newPapa->save();
    QMessageBox msgBox;
    msgBox.setText(tr("L'utilisateur a bien ete cr�e"));
    msgBox.exec();
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

        if (user->level() == LEVEL_FAMILY)
        {
            mylist.append(user);
        }
    }
    return mylist;
}


void ManageStudents::refreshall()
{
    qDebug() << "Refresh all";
    edit->setEnabled(false);
    del->setEnabled(false);
    StudentList->updateall();
}