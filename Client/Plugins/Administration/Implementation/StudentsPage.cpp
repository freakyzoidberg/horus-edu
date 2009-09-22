#include "StudentsPage.h"

#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QBuffer>
#include <QMenu>
#include <qvariant.h>

StudentsPage::StudentsPage(TreeDataPlugin* tree, UserDataPlugin *users)
{
    user = 0;
    setupUi();
    _users = users;
    studentTree->setModel(new StudentModel(_users->getAllUser(), 3));
    studentTree->setColumnWidth(0, 35);
    studentTree->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(studentTree, SIGNAL(customContextMenuRequested(const QPoint&)),this, SLOT(ShowTreeContextMenu(const QPoint&)));
    connect(buttonBox, SIGNAL(clicked(QAbstractButton *)), this, SLOT(buttonClicked(QAbstractButton *)));
    connect(studentTree->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(userSelected(QModelIndex)));
    connect(imageButton, SIGNAL(clicked()), this, SLOT(ImageButtonClick()));
}


void    StudentsPage::ShowTreeContextMenu(const QPoint& pnt)
{
  QList<QAction *> actions;
  if (studentTree->indexAt(pnt).isValid())
  {
        QAction *actAdd = new QAction(tr("Ajouter"), this);
        QAction *actEdit = new QAction(tr("Edit"), this);
        QAction *actRen = new QAction(tr("Rename"), this);
        QAction *actDel = new QAction(tr("Delete"), this);
        actions.append(actAdd);
        actions.append(actEdit);
        actions.append(actRen);
        actions.append(actDel);

  }
  if (actions.count() > 0)
    QMenu::exec(actions, studentTree->mapToGlobal(pnt));
}

void    StudentsPage::ImageButtonClick()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
     if (!fileName.isEmpty())
    {

         image.load(fileName);
         if (image.isNull())
         {
             qDebug() << fileName;
             QMessageBox::information(this, tr("Image Viewer"),
                                      tr("Cannot load %1.").arg(fileName));
             return;
         }
            imageLabel->setPixmap(QPixmap::fromImage(image));
            imageLabel->show();
        }

}

void StudentsPage::userSelected(const QModelIndex &userIndex)
{
    user = static_cast<UserData*>(userIndex.internalPointer());
    loginTxt->setText(user->login());
    nomTxt->setText(user->name());
    prenomTxt->setText(user->surname());
    languageTxt->setText(user->language());
    addrTxt->setText(user->address());
    phoneTxt->setText(user->phone());
    paysTxt->setText(user->country());
    //imageLabel->setPixmap(QPixmap::fromImage(user->picture().value<QImage>()));
    //qDebug() << user->picture();
}

void    StudentsPage::setupUi()
{
    this->setMinimumWidth(700);
    stuLayout = new QHBoxLayout(this);
    studentTree = new QTreeView();
    studentTree->setAnimated(true);
    menuLayout = new QVBoxLayout();
    //menuLayout->setAlignment(Qt::AlignHCenter);
    formLayout = new QHBoxLayout();
    leftLayout = new QFormLayout();
    leftLayout->setHorizontalSpacing(4);
    leftLayout->setVerticalSpacing(10);
    label = new QLabel("Login");
    leftLayout->setWidget(1, QFormLayout::LabelRole, label);
    loginTxt = new QLineEdit();
    leftLayout->setWidget(1, QFormLayout::FieldRole, loginTxt);
    label_12 = new QLabel("Password");
    leftLayout->setWidget(2, QFormLayout::LabelRole, label_12);
    passTxt = new QLineEdit(this);
    passTxt->setEchoMode(QLineEdit::Password);
    leftLayout->setWidget(2, QFormLayout::FieldRole, passTxt);
    date = new QCalendarWidget();
    date->setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
    leftLayout->setWidget(3, QFormLayout::FieldRole, date);
    label_2 = new QLabel("Name");
    leftLayout->setWidget(4, QFormLayout::LabelRole, label_2);
    nomTxt = new QLineEdit(this);
    leftLayout->setWidget(4, QFormLayout::FieldRole, nomTxt);
    label_3 = new QLabel("Surname");
    leftLayout->setWidget(5, QFormLayout::LabelRole, label_3);
    prenomTxt = new QLineEdit(this);
    leftLayout->setWidget(5, QFormLayout::FieldRole, prenomTxt);
    label_4 = new QLabel("Phone");
    leftLayout->setWidget(6, QFormLayout::LabelRole, label_4);
    phoneTxt = new QLineEdit(this);
    leftLayout->setWidget(6, QFormLayout::FieldRole, phoneTxt);
    label_7 = new QLabel("Address");
    leftLayout->setWidget(7, QFormLayout::LabelRole, label_7);
    addrTxt = new QLineEdit(this);
    leftLayout->setWidget(7, QFormLayout::FieldRole, addrTxt);
    label_8 = new QLabel("Country");
    leftLayout->setWidget(8, QFormLayout::LabelRole, label_8);
    paysTxt = new QLineEdit(this);
    leftLayout->setWidget(8, QFormLayout::FieldRole, paysTxt);
    label_11 = new QLabel("Language");
    leftLayout->setWidget(9, QFormLayout::LabelRole, label_11);
    languageTxt = new QLineEdit(this);
    languageTxt->setObjectName(QString::fromUtf8("languageTxt"));
    leftLayout->setWidget(9, QFormLayout::FieldRole, languageTxt);
    activeBox = new QCheckBox("Active");
    activeBox->setObjectName(QString::fromUtf8("activeBox"));
    leftLayout->setWidget(0, QFormLayout::FieldRole, activeBox);
    formLayout->addLayout(leftLayout);
    rightLayout = new QFormLayout();
    rightLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    rightLayout->setHorizontalSpacing(4);
    rightLayout->setVerticalSpacing(10);
    imageButton = new QPushButton("Image");
    rightLayout->setWidget(3, QFormLayout::FieldRole, imageButton);
    imageLabel = new QLabel("");
    imageLabel->setMargin(2);
    rightLayout->setWidget(2, QFormLayout::FieldRole, imageLabel);
    classTxt = new QLineEdit(this);
    classTxt->setObjectName(QString::fromUtf8("classTxt"));
    rightLayout->setWidget(0, QFormLayout::FieldRole, classTxt);
    label_5 = new QLabel("Classe");
    label_5->setObjectName(QString::fromUtf8("label_5"));
    rightLayout->setWidget(0, QFormLayout::LabelRole, label_5);
    formLayout->addLayout(rightLayout);
    menuLayout->addLayout(formLayout);
    buttonBox = new QDialogButtonBox(Qt::Horizontal, this);

    buttonBox->addButton(new QPushButton("Add"), QDialogButtonBox::ActionRole);
    buttonBox->addButton(new QPushButton("Save"), QDialogButtonBox::ActionRole);
    buttonBox->addButton(new QPushButton("Cancel"), QDialogButtonBox::ActionRole);
    buttonBox->addButton(new QPushButton("Delete"), QDialogButtonBox::ActionRole);
    menuLayout->addWidget(buttonBox);
    stuLayout->addWidget(studentTree);
    stuLayout->addLayout(menuLayout);
    formLayout->setStretch(0, 1);
    formLayout->setStretch(1, 1);
    this->stuLayout->setStretch(0, 1);
    this->stuLayout->setStretch(1, 4);
}

void StudentsPage::buttonClicked(QAbstractButton * button)
{
   if (button->text() == "Add")
   {
        createUser();
   }
   else if (button->text() == "Save")
   {
        editUser();
   }
   else if (button->text() == "Cancel")
   {
        cancelUser();
   }
   else if (button->text() == "Delete")
   {
        deleteUser();
   }
}

void    StudentsPage::editUser()
{
    QMessageBox msgBox;
    msgBox.setText("Confirme modification");
    msgBox.setInformativeText("Do you want to confirme the modification");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    if (ret == QMessageBox::Yes)
    {
        if (user == 0)
        {
            return;
        }
        user->setName(nomTxt->text());
        user->setSurname(prenomTxt->text());
        user->setLanguage(languageTxt->text());
        user->setAddress(addrTxt->text());
        user->setPhone(phoneTxt->text());
        user->setBirthDate(this->date->selectedDate());
        user->setCountry(this->paysTxt->text());
        user->setPicture(imageLabel->pixmap());
        user->setPicture("vide");
        user->enable(true);
        user->setLevel(3);
        user->save();
        loginTxt->setText("");
        nomTxt->setText("");
        passTxt->setText("");
        prenomTxt->setText("");
        languageTxt->setText("");
        addrTxt->setText("");
        phoneTxt->setText("");
        paysTxt->setText("");
//        imageLabel->clear();
    }
    return;
}
void    StudentsPage::cancelUser()
{
    QMessageBox msgBox;
    msgBox.setText("Confirme cancel");
    msgBox.setInformativeText("Do you want to cancel the modification");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    if (ret == QMessageBox::Yes)
    {
        loginTxt->setText("");
        nomTxt->setText("");
        passTxt->setText("");
        prenomTxt->setText("");
        languageTxt->setText("");
        addrTxt->setText("");
        phoneTxt->setText("");
        paysTxt->setText("");
  //      imageLabel->clear();
    }
    return;
}

void    StudentsPage::deleteUser()
{

}

void    StudentsPage::createUser()
{
    QMessageBox msgBox;
    QString      Error = "";
    if(this->loginTxt->text() == "")
        Error.append("Login |");
    if(this->addrTxt->text() == "")
        Error.append("Address |");
    if(this->paysTxt->text() == "")
        Error.append("Country |");
    if(this->phoneTxt->text() == "")
        Error.append("Phone |");
    if(this->passTxt->text() == "")
        Error.append("Password |");
    if(this->languageTxt->text() == "")
        Error.append("Language |");
    if(this->prenomTxt->text() == "")
        Error.append("Prenom |");
    if(this->nomTxt->text() == "")
        Error.append("Nom |");
    if (Error != "")
    {
        QString msg;
        msg.append("les champs suivant doivent etre remplis: \n");
        msg.append(Error);

        msgBox.setText(msg);
        msgBox.exec();
        return;
    }
    UserData *data = _users->createUser(loginTxt->text());
    data->setName(nomTxt->text());
    data->setSurname(prenomTxt->text());
    data->setLanguage(languageTxt->text());
    data->setAddress(addrTxt->text());
    data->setPhone(phoneTxt->text());
    data->setBirthDate(this->date->selectedDate());
    data->setCountry(this->paysTxt->text());
    data->enable(true);
    data->setPicture("vide");
    /*if(imageLabel->pixmap()->height() == 0)
        data->setPicture("vide");
    else
        data->setPicture(imageLabel->pixmap());*/
    data->setLevel(3);

    data->save();
    loginTxt->setText("");
    nomTxt->setText("");
    passTxt->setText("");
    prenomTxt->setText("");
    languageTxt->setText("");
    addrTxt->setText("");
    phoneTxt->setText("");
    paysTxt->setText("");
    //imageLabel->clear();
    studentTree->reset();
    //studentTree->setModel(new StudentModel(_users->getAllUser(), 1));
    //connect(studentTree->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(userSelected(QModelIndex)));
    msgBox.setText("The user was succefully created");
    msgBox.exec();

}
