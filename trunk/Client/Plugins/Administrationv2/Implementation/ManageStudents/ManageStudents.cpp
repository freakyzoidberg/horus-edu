/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "ManageStudents.h"
#include <QDebug>
#include <QMessageBox>

ManageStudents::ManageStudents(TreeDataPlugin *treeplugin, UserDataPlugin *userplugin)
{
    UD = userplugin;
    TD = treeplugin;
	newUSer = NULL;
	newPapa = NULL; //lol
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
    connect(StudentList->StudentList, SIGNAL(itemSelectionChanged ()), this, SLOT(checkedit()));


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
QMessageBox *box;
int res;

    if (StudentList->StudentList->selectedItems().count() > 0)
    {
        UserData* myuser = UD->user(StudentList->StudentList->selectedItems().first()->data(Qt::UserRole).toInt());
  box = new QMessageBox(QMessageBox::Question, tr("Confirmation"), tr("Do you really want to delete ") + StudentList->StudentList->selectedItems().first()->text() + tr(" ?"), QMessageBox::Yes | QMessageBox::No, this);
  res = box->exec();
   if (res == QMessageBox::Yes)
  {

        myuser->remove();
        seteditfalse();
        if (StudentList->ClassList->selectedItems().count() > 0)
            StudentList->updatestudents(StudentList->ClassList->selectedItems().first());
        if (info)
        {
            delete info;
            info = 0;
        }
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
    int flag = 0;
    if ((scrollStudentForm) &&  (scrollStudentForm->StudentForm))
    {
        if (!scrollStudentForm->StudentForm->BaseInfos->getName().isEmpty() &&
            !scrollStudentForm->StudentForm->BaseInfos->getSurName().isEmpty())
        {
            if (scrollStudentForm->StudentForm->id == 0)
            {
                newUSer = UD->createUser(scrollStudentForm->StudentForm->BaseInfos->getName());
                newPapa = UD->createUser(scrollStudentForm->StudentForm->ParInfos->getlastN());
                //connect(newUSer, SIGNAL(created()), newPapa, SLOT(create())); //A Corriger ne marche plus depuis le r1649
                newMomy = UD->createUser(scrollStudentForm->StudentForm->ParInfos->getlastN2());
                //connect(newPapa, SIGNAL(created()), newMomy, SLOT(create())); //A Corriger ne marche plus depuis le r1649
                //connect(newMomy, SIGNAL(created()), this, SLOT(userCreated())); //A Corriger ne marche plus depuis le r1649
            }
            else
            {
                newUSer = UD->user(scrollStudentForm->StudentForm->id);

                if (UD->parentsOfStudent(newUSer).count() > 0)
                {
                	newPapa = UD->parentsOfStudent(newUSer)[0];
                        if (UD->parentsOfStudent(newUSer).count() > 1)
                        {
                            newMomy = UD->parentsOfStudent(newUSer)[1];
                            flag = 2;
                        }
                        else if (newPapa->gender() == GENDER_FEMALE)
                        {
                            newMomy = UD->parentsOfStudent(newUSer)[0];
                            newPapa = UD->createUser(scrollStudentForm->StudentForm->ParInfos->getlastN());
                            //connect(newPapa, SIGNAL(created()), this, SLOT(userCreated())); //A Corriger ne marche plus depuis le r1649
                            flag = 3;
                        }
                        else
                        {
                            newMomy = UD->createUser(scrollStudentForm->StudentForm->ParInfos->getlastN2());
                            //connect(newMomy, SIGNAL(created()), this, SLOT(userCreated())); //A Corriger ne marche plus depuis le r1649
                            flag = 4;
                        }

                }
                else
                {
                   newPapa = UD->createUser(scrollStudentForm->StudentForm->ParInfos->getlastN());
                   newMomy = UD->createUser(scrollStudentForm->StudentForm->ParInfos->getlastN2());
//                  connect(newPapa, SIGNAL(created()), newMomy, SLOT(create()));  A Corriger ne marche plus depuis le r1649
                   //connect(newMomy, SIGNAL(created()), this, SLOT(userCreated())); //A Corriger ne marche plus depuis le r1649
                   flag = 5;
                }
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
            newUSer->setBornPlace(scrollStudentForm->StudentForm->BaseInfos->getBplace());
            //BasicInfos
            newUSer->setSurname(scrollStudentForm->StudentForm->BaseInfos->getSurName());
            newUSer->setAddress(scrollStudentForm->StudentForm->BaseInfos->getAddress());
            newUSer->setBirthDate(scrollStudentForm->StudentForm->BaseInfos->getBday());
            newUSer->setNbrBrothers(scrollStudentForm->StudentForm->BaseInfos->getbrocount());
            newUSer->setMail(scrollStudentForm->StudentForm->BaseInfos->getEmail());
            //Social Infos
            newUSer->setSubscriptionReason(scrollStudentForm->StudentForm->SocInfos->getMotif());
            newUSer->setComment(scrollStudentForm->StudentForm->SocInfos->getReferent()+"|:/:|:/|"+scrollStudentForm->StudentForm->SocInfos->getAides()+"|:/:|:/|");
            //Scholar infos
            newUSer->setRepeatedYears(scrollStudentForm->StudentForm->SchoInfos->getNb_red());
            newUSer->setStartYear(scrollStudentForm->StudentForm->SchoInfos->getStartYear());
            newUSer->setLeaveYear(scrollStudentForm->StudentForm->SchoInfos->getLeftYear());
            //Suivi
            newUSer->setFollowUp(scrollStudentForm->StudentForm->SuiInfos->getSuivi());


            //Parents info

            newPapa->setEnable(true);
            newPapa->setSurname(scrollStudentForm->StudentForm->ParInfos->getfirsN());
            newPapa->setRelationship(scrollStudentForm->StudentForm->ParInfos->getrela());
            newPapa->setAddress(scrollStudentForm->StudentForm->ParInfos->getaddr());
            newPapa->setMail(scrollStudentForm->StudentForm->ParInfos->getmail());
            newPapa->setPhone1(scrollStudentForm->StudentForm->ParInfos->gethomeP());
            newPapa->setPhone2(scrollStudentForm->StudentForm->ParInfos->getworkP());
            newPapa->setPhone3(scrollStudentForm->StudentForm->ParInfos->getmobileP());
            newPapa->setOccupation(scrollStudentForm->StudentForm->ParInfos->getoccuField());
            newPapa->setProCategory(scrollStudentForm->StudentForm->ParInfos->getoccuC());
            newPapa->setGender(GENDER_MALE);
            newPapa->setLevel(LEVEL_FAMILY);
            if (flag == 3 || flag == 5)
                newPapa->create();

            newMomy->setEnable(true);
            newMomy->setSurname(scrollStudentForm->StudentForm->ParInfos->getfirsN2());
            newMomy->setRelationship(scrollStudentForm->StudentForm->ParInfos->getrela());
            newMomy->setAddress(scrollStudentForm->StudentForm->ParInfos->getaddr());
            newMomy->setMail(scrollStudentForm->StudentForm->ParInfos->getmail());
            newMomy->setPhone1(scrollStudentForm->StudentForm->ParInfos->gethomeP());
            newMomy->setPhone2(scrollStudentForm->StudentForm->ParInfos->getworkP());
            newMomy->setPhone3(scrollStudentForm->StudentForm->ParInfos->getmobileP());
            newMomy->setOccupation(scrollStudentForm->StudentForm->ParInfos->getoccuField2());
            newMomy->setProCategory(scrollStudentForm->StudentForm->ParInfos->getoccuC2());
            newMomy->setGender(GENDER_FEMALE);
            newMomy->setLevel(LEVEL_FAMILY);
            if (flag == 4 || flag == 5)
                newMomy->create();


            //newUSer->setRelationship(QVariant(x).toString());

            newUSer->setEnable(true);

            if (scrollStudentForm->StudentForm->id == 0)
            {
                newUSer->create();
                scrollStudentForm->StudentForm->id = newUSer->id();
                newPapa->create();
                newMomy->create();
                newPapa->setStudent(newUSer);
                newMomy->setStudent(newUSer);
            }
            else
            {
                newUSer->save();
                if (flag == 2)
                {
                    newPapa->save();
                    newMomy->save();
                }
                else if (flag == 3)
                    newMomy->save();
                else if (flag == 4)
                    newPapa->save();
            }
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
    int flag = 0;
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
              //  connect(newUSer, SIGNAL(created()), newPapa, SLOT(create())); c
                newMomy = UD->createUser(scrollStudentForm->StudentForm->ParInfos->getlastN2());
                //connect(newPapa, SIGNAL(created()), newMomy, SLOT(create())); //A Corriger ne marche plus depuis le r1649
                //connect(newMomy, SIGNAL(created()), this, SLOT(userCreated())); A Corriger ne marche plus depuis le r1649
            }
            else
            {
                newUSer = UD->user(scrollStudentForm->StudentForm->id);
                if (UD->parentsOfStudent(newUSer).count() > 0)
                {
                        newPapa = UD->parentsOfStudent(newUSer)[0];
                        if (UD->parentsOfStudent(newUSer).count() > 1)
                        {
                            newMomy = UD->parentsOfStudent(newUSer)[1];
                            flag = 2;
                        }
                        else if (newPapa->gender() == GENDER_FEMALE)
                        {
                            newMomy = UD->parentsOfStudent(newUSer)[0];
                            newPapa = UD->createUser(scrollStudentForm->StudentForm->ParInfos->getlastN());
                  //          connect(newPapa, SIGNAL(created()), this, SLOT(userCreated())); A Corriger ne marche plus depuis le r1649
                            flag = 3;
                        }
                        else
                        {
                            newMomy = UD->createUser(scrollStudentForm->StudentForm->ParInfos->getlastN2());
                    //        connect(newMomy, SIGNAL(created()), this, SLOT(userCreated())); A Corriger ne marche plus depuis le r1649
                            flag = 4;
                        }

                }
                else
                {
                   newPapa = UD->createUser(scrollStudentForm->StudentForm->ParInfos->getlastN());
                   newMomy = UD->createUser(scrollStudentForm->StudentForm->ParInfos->getlastN2());
                   //connect(newPapa, SIGNAL(created()), newMomy, SLOT(create())); // A Corriger ne marche plus depuis le r1649
                   // connect(newMomy, SIGNAL(created()), this, SLOT(userCreated())); //A Corriger ne marche plus depuis le r1649
                   flag = 5;
                }
            }

            //Data
            newUSer->setName(scrollStudentForm->StudentForm->BaseInfos->getName());
            newUSer->setLevel(LEVEL_STUDENT);
            newUSer->setStudentClass(TD->node(scrollStudentForm->getnodeid()));
            newUSer->setPassword(scrollStudentForm->StudentForm->BaseInfos->getSurName());
            newUSer->setBornPlace(scrollStudentForm->StudentForm->BaseInfos->getBplace());
            //BasicInfos
            newUSer->setSurname(scrollStudentForm->StudentForm->BaseInfos->getSurName());
            newUSer->setAddress(scrollStudentForm->StudentForm->BaseInfos->getAddress());
            newUSer->setBirthDate(scrollStudentForm->StudentForm->BaseInfos->getBday());
            newUSer->setNbrBrothers(scrollStudentForm->StudentForm->BaseInfos->getbrocount());
            newUSer->setMail(scrollStudentForm->StudentForm->BaseInfos->getEmail());
            //Social Infos
            newUSer->setSubscriptionReason(scrollStudentForm->StudentForm->SocInfos->getMotif());
            newUSer->setComment(scrollStudentForm->StudentForm->SocInfos->getReferent()+"|:/:|:/|"+scrollStudentForm->StudentForm->SocInfos->getAides()+"|:/:|:/|");
            //Scholar infos
            newUSer->setRepeatedYears(scrollStudentForm->StudentForm->SchoInfos->getNb_red());
            newUSer->setStartYear(scrollStudentForm->StudentForm->SchoInfos->getStartYear());
            newUSer->setLeaveYear(scrollStudentForm->StudentForm->SchoInfos->getLeftYear());
            //Suivi infos
            newUSer->setFollowUp(scrollStudentForm->StudentForm->SuiInfos->getSuivi());

            //Parent's Infos
	    
            newPapa->setEnable(true);
            newPapa->setAddress(scrollStudentForm->StudentForm->ParInfos->getaddr());
            newPapa->setName(scrollStudentForm->StudentForm->ParInfos->getlastN());
            newPapa->setSurname(scrollStudentForm->StudentForm->ParInfos->getfirsN());
            newPapa->setRelationship(scrollStudentForm->StudentForm->ParInfos->getrela());
            newPapa->setAddress(scrollStudentForm->StudentForm->ParInfos->getaddr());
            newPapa->setMail(scrollStudentForm->StudentForm->ParInfos->getmail());
            newPapa->setPhone1(scrollStudentForm->StudentForm->ParInfos->gethomeP());
            newPapa->setPhone2(scrollStudentForm->StudentForm->ParInfos->getworkP());
            newPapa->setPhone3(scrollStudentForm->StudentForm->ParInfos->getmobileP());
            newPapa->setOccupation(scrollStudentForm->StudentForm->ParInfos->getoccuField());
            newPapa->setProCategory(scrollStudentForm->StudentForm->ParInfos->getoccuC());
            newPapa->setGender(GENDER_MALE);
            newPapa->setLevel(LEVEL_FAMILY);
            if (flag == 3 || flag == 5)
                newPapa->create();

            newMomy->setEnable(true);
            newMomy->setSurname(scrollStudentForm->StudentForm->ParInfos->getfirsN2());
            newMomy->setName(scrollStudentForm->StudentForm->ParInfos->getlastN2());
            newMomy->setRelationship(scrollStudentForm->StudentForm->ParInfos->getrela());
            newMomy->setAddress(scrollStudentForm->StudentForm->ParInfos->getaddr());
            newMomy->setMail(scrollStudentForm->StudentForm->ParInfos->getmail());
            newMomy->setPhone1(scrollStudentForm->StudentForm->ParInfos->gethomeP());
            newMomy->setPhone2(scrollStudentForm->StudentForm->ParInfos->getworkP());
            newMomy->setPhone3(scrollStudentForm->StudentForm->ParInfos->getmobileP());
            newMomy->setOccupation(scrollStudentForm->StudentForm->ParInfos->getoccuField2());
            newMomy->setProCategory(scrollStudentForm->StudentForm->ParInfos->getoccuC2());
            newMomy->setGender(GENDER_FEMALE);
            newMomy->setLevel(LEVEL_FAMILY);
            if (flag == 4 || flag == 5)
                newMomy->create();





                //ClasseNextYear


   // connect(UD, dataUpdated(newUSer), StudentList->updatestudents(StudentList->ClassList->selectedItems().first()));
            newUSer->setEnable(true);
            if (scrollStudentForm->StudentForm->id == 0)
            {
                newUSer->create();
                scrollStudentForm->StudentForm->id = newUSer->id();
                newPapa->create();            
                newMomy->create();
                newPapa->setStudent(newUSer);
                newMomy->setStudent(newUSer);
            }
            else
            {
                newUSer->save();
                if (flag == 2)
                {
                    newPapa->save();
                    newMomy->save();
                }
                else if (flag == 3)
                    newMomy->save();
                else if (flag == 4)
                    newPapa->save();
            }

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

void ManageStudents::userCreated()
{
    disconnect(this, SLOT(userCreated()));
    if (newPapa->student() == UD->nobody())
    {
        newPapa->setStudent(newUSer);
        newPapa->save();
    }
    if (newMomy->student() == UD->nobody())
    {
        newMomy->setStudent(newUSer);
        newMomy->save();
    }
//    QMessageBox msgBox;
//    msgBox.setText(tr("L'utilisateur a bien"));
//    msgBox.exec();
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
    if (StudentList->StudentList->selectedItems().count() > 0)
    {
    info = new InfoPanel(UD->user(StudentList->StudentList->selectedItems().first()->data(Qt::UserRole).toInt()));
    informationsLayout->addWidget(info);
    }
}

void ManageStudents::checkedit()
{
if (StudentList->StudentList->selectedItems().count() > 0)
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
else
{
      if (info)
    {
        delete info;
        info = 0;
    }
     edit->setEnabled(false);
     del->setEnabled(false);
}
}

QList<UserData*> ManageStudents::getAllParents()
{
    QList<UserData*> mylist;

	foreach (Data* data, UD->allDatas())
    {
		UserData* user = (UserData*)data;
        if (user->level() == LEVEL_FAMILY)
        {
            mylist.append(user);
        }
    }
    return mylist;
}


void ManageStudents::refreshall()
{

    edit->setEnabled(false);
    del->setEnabled(false);
    StudentList->updateall();
}
