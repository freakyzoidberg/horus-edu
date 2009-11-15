#include "UserForm.h"

#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QBuffer>
#include <QMenu>
#include <qvariant.h>

#include "UserPage.h"

UserForm::UserForm(TreeData* treeNode, UserData *_user, UserDataPlugin *_users, UserPage *_page) : users(_users), page(_page)
{
    user = _user;
    node = treeNode;
    setupUi();

    connect(buttonBox, SIGNAL(clicked(QAbstractButton *)), this, SLOT(buttonClicked(QAbstractButton *)));
    connect(imageButton, SIGNAL(clicked()), this, SLOT(ImageButtonClick()));
    fillUserFields();
    buttonBox->addButton(new QPushButton(tr("Save")), QDialogButtonBox::ActionRole);
    buttonBox->addButton(new QPushButton(tr("Cancel")), QDialogButtonBox::ActionRole);
}

UserForm::UserForm(TreeData* treeNode, UserDataPlugin *_users, UserPage *_page) : users(_users), page(_page)
{
    node = treeNode;
    setupUi();
    connect(buttonBox, SIGNAL(clicked(QAbstractButton *)), this, SLOT(buttonClicked(QAbstractButton *)));
    connect(imageButton, SIGNAL(clicked()), this, SLOT(ImageButtonClick()));
    clearForm();
    buttonBox->addButton(new QPushButton(tr("Add")), QDialogButtonBox::ActionRole);
    buttonBox->addButton(new QPushButton(tr("Cancel")), QDialogButtonBox::ActionRole);
}

void    UserForm::ImageButtonClick()
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

void UserForm::fillUserFields()
{
    loginTxt->setText(user->login());
    nomTxt->setText(user->name());
    prenomTxt->setText(user->surname());
    languageTxt->setText(user->language());
    addrTxt->setText(user->address());
    phoneTxt->setText(user->phone1());
    paysTxt->setText(user->country());
    if (user->level() == 2)
        typeBox->setCurrentIndex(1);
    else
        typeBox->setCurrentIndex(0);
    //imageLabel->setPixmap(QPixmap::fromImage(user->picture().value<QImage>()));
    //qDebug() << user->picture();
}

void    UserForm::setupUi()
{
    this->setMinimumWidth(600);
    stuLayout = new QHBoxLayout(this);
    menuLayout = new QVBoxLayout();
    //menuLayout->setAlignment(Qt::AlignHCenter);
    formLayout = new QHBoxLayout();
    leftLayout = new QFormLayout();
    leftLayout->setHorizontalSpacing(4);
    leftLayout->setVerticalSpacing(10);
    label = new QLabel(tr("Login"));
    leftLayout->setWidget(1, QFormLayout::LabelRole, label);
    loginTxt = new QLineEdit();
    leftLayout->setWidget(1, QFormLayout::FieldRole, loginTxt);
    label_1 = new QLabel(tr("Password"));
    leftLayout->setWidget(2, QFormLayout::LabelRole, label_1);
    passTxt = new QLineEdit(this);
    passTxt->setEchoMode(QLineEdit::Password);
    leftLayout->setWidget(2, QFormLayout::FieldRole, passTxt);
    date = new QCalendarWidget();
    date->setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
    leftLayout->setWidget(3, QFormLayout::FieldRole, date);
    label_2 = new QLabel(tr("Name"));
    leftLayout->setWidget(4, QFormLayout::LabelRole, label_2);
    nomTxt = new QLineEdit(this);
    leftLayout->setWidget(4, QFormLayout::FieldRole, nomTxt);
    label_3 = new QLabel(tr("Surname"));
    leftLayout->setWidget(5, QFormLayout::LabelRole, label_3);
    prenomTxt = new QLineEdit(this);
    leftLayout->setWidget(5, QFormLayout::FieldRole, prenomTxt);
    label_4 = new QLabel(tr("Phone"));
    leftLayout->setWidget(6, QFormLayout::LabelRole, label_4);
    phoneTxt = new QLineEdit(this);
    leftLayout->setWidget(6, QFormLayout::FieldRole, phoneTxt);
    label_7 = new QLabel(tr("Address"));
    leftLayout->setWidget(7, QFormLayout::LabelRole, label_7);
    addrTxt = new QLineEdit(this);
    leftLayout->setWidget(7, QFormLayout::FieldRole, addrTxt);
    label_8 = new QLabel(tr("Country"));
    leftLayout->setWidget(8, QFormLayout::LabelRole, label_8);
    paysTxt = new QLineEdit(this);
    leftLayout->setWidget(8, QFormLayout::FieldRole, paysTxt);
    label_11 = new QLabel(tr("Language"));
    leftLayout->setWidget(9, QFormLayout::LabelRole, label_11);
    languageTxt = new QLineEdit(this);
    languageTxt->setObjectName(QString::fromUtf8("languageTxt"));
    leftLayout->setWidget(9, QFormLayout::FieldRole, languageTxt);
    activeBox = new QCheckBox(tr("Active"));
    activeBox->setObjectName(QString::fromUtf8("activeBox"));
    leftLayout->setWidget(0, QFormLayout::FieldRole, activeBox);
    formLayout->addLayout(leftLayout);
    rightLayout = new QFormLayout();
    rightLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    rightLayout->setHorizontalSpacing(4);
    rightLayout->setVerticalSpacing(10);
    imageButton = new QPushButton(tr("Image"));
    rightLayout->setWidget(3, QFormLayout::FieldRole, imageButton);
    imageLabel = new QLabel("");
    imageLabel->setMargin(2);
    rightLayout->setWidget(2, QFormLayout::FieldRole, imageLabel);
    classTxt = new QLineEdit(this);
    classTxt->setObjectName(QString::fromUtf8("classTxt"));
    rightLayout->setWidget(1, QFormLayout::FieldRole, classTxt);
    label_5 = new QLabel(tr("Classe"));
    label_5->setObjectName(QString::fromUtf8("label_5"));
    rightLayout->setWidget(1, QFormLayout::LabelRole, label_5);
    label_6 = new QLabel(tr("Type"));
    rightLayout->setWidget(0, QFormLayout::LabelRole, label_6);
    typeBox = new QComboBox(this);
    typeBox->addItem(QIcon(":/images/GroupIcon.png"), tr("Etudiant"));
    typeBox->addItem(QIcon(":/images/GradeIcon.png"), tr("Professeur"));
    rightLayout->setWidget(0, QFormLayout::FieldRole, typeBox);
    formLayout->addLayout(rightLayout);
    menuLayout->addLayout(formLayout);
    buttonBox = new QDialogButtonBox(Qt::Horizontal, this);
    menuLayout->addWidget(buttonBox);
    stuLayout->addLayout(menuLayout);
    formLayout->setStretch(0, 1);
    formLayout->setStretch(1, 1);
    this->stuLayout->setStretch(0, 1);
}

void UserForm::buttonClicked(QAbstractButton * button)
{
   if (button->text() == tr("Add"))
   {
        createNewUser();
   }
   else if (button->text() == tr("Save"))
   {
        editUser();
   }
   else if (button->text() == tr("Cancel"))
   {
        cancelUser();
   }
}

void    UserForm::editUser()
{
    QMessageBox msgBox;
    msgBox.setText(tr("Confirme modification"));
    msgBox.setInformativeText(tr("Do you want to confirme the modification"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    if (ret == QMessageBox::Yes)
    {
        user->setName(nomTxt->text());
        user->setSurname(prenomTxt->text());
        user->setLanguage(languageTxt->text());
        user->setAddress(addrTxt->text());
        user->setPhone1(phoneTxt->text());
        user->setBirthDate(this->date->selectedDate());
        user->setCountry(this->paysTxt->text());
        user->setPicture(imageLabel->pixmap());
        user->setPicture("vide");
        user->enable(true);
        if (typeBox->currentText() == "Professeur")
            user->setLevel(2);
        else
            user->setLevel(3);
        user->save();
        clearForm();
        this->close();
        //page->resetPage();
    }
    return;
}
void    UserForm::cancelUser()
{
    QMessageBox msgBox;
    msgBox.setText(tr("Confirme cancel"));
    msgBox.setInformativeText(tr("Do you want to cancel the modification"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    if (ret == QMessageBox::Yes)
    {
        clearForm();
    }
    return;
}

void    UserForm::clearForm()
{
        loginTxt->setText("");
        nomTxt->setText("");
        passTxt->setText("");
        prenomTxt->setText("");
        languageTxt->setText("");
        addrTxt->setText("");
        phoneTxt->setText("");
        paysTxt->setText("");
        activeBox->setChecked(false);
  //      imageLabel->clear();
}

void    UserForm::deleteUser()
{

}

void    UserForm::createNewUser()
{
    QMessageBox msgBox;
    QString      Error = "";
    if(this->loginTxt->text() == "")
        Error.append(tr("Login |"));
    if(this->addrTxt->text() == "")
        Error.append(tr("Address |"));
    if(this->paysTxt->text() == "")
        Error.append(tr("Country |"));
    if(this->phoneTxt->text() == "")
        Error.append(tr("Phone |"));
    if(this->passTxt->text() == "")
        Error.append(tr("Password |"));
    if(this->languageTxt->text() == "")
        Error.append(tr("Language |"));
    if(this->prenomTxt->text() == "")
        Error.append(tr("Prenom |"));
    if(this->nomTxt->text() == "")
        Error.append(tr("Nom |"));
    if (Error != "")
    {
        QString msg;
        msg.append(tr("les champs suivant doivent etre remplis: \n"));
        Error.chop(1);
        msg.append(Error);

        msgBox.setText(msg);
        msgBox.exec();
        return;
    }
    UserData *data = users->createUser(loginTxt->text());
    data->setName(nomTxt->text());
    data->setSurname(prenomTxt->text());
    data->setLanguage(languageTxt->text());
    data->setPassword(passTxt->text());
    data->setAddress(addrTxt->text());
    data->setPhone(phoneTxt->text());
    data->setBirthDate(this->date->selectedDate());
    data->setCountry(this->paysTxt->text());
    data->enable(true);
    data->setPicture("vide");
    if (typeBox->currentText() == "Professeur")
        data->setLevel(2);
    else
        data->setLevel(3);
    data->setNode(node);
    data->create();
    clearForm();
    msgBox.setText(tr("The user was succefully created"));
    msgBox.exec();
    //page->resetPage();
    this->close();
}
