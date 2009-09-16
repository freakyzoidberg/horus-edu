#include "StudentsPage.h"

#include <QDebug>
#include <QMessageBox>

StudentsPage::StudentsPage(TreeDataPlugin* tree, UserDataPlugin *users)
{
    user = 0;
    setupUi();
    _users = users;
    studentTree->setModel(new StudentModel(users->getAllUser(), 1));
    connect(buttonBox, SIGNAL(clicked(QAbstractButton *)), this, SLOT(buttonClicked(QAbstractButton *)));
    connect(studentTree->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(userSelected(QModelIndex)));
}

void StudentsPage::userSelected(const QModelIndex &userIndex)
{
    user = static_cast<UserData*>(userIndex.internalPointer());
    loginTxt->setText(user->login());
    nomTxt->setText(user->name());
    prenomTxt->setText(user->surname());
    languageTxt->setText(user->language());
}

void    StudentsPage::setupUi()
{
    this->setMinimumWidth(700);
    stuLayout = new QHBoxLayout(this);
    studentTree = new QTreeView();
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
    leftLayout->setWidget(3, QFormLayout::FieldRole, date);
    label_2 = new QLabel("Nom");
    leftLayout->setWidget(4, QFormLayout::LabelRole, label_2);
    nomTxt = new QLineEdit(this);
    leftLayout->setWidget(4, QFormLayout::FieldRole, nomTxt);
    label_3 = new QLabel("Prenom");
    leftLayout->setWidget(5, QFormLayout::LabelRole, label_3);
    prenomTxt = new QLineEdit(this);
    leftLayout->setWidget(5, QFormLayout::FieldRole, prenomTxt);
    label_4 = new QLabel("Telephone");
    leftLayout->setWidget(6, QFormLayout::LabelRole, label_4);
    phoneTxt = new QLineEdit(this);
    leftLayout->setWidget(6, QFormLayout::FieldRole, phoneTxt);
    label_6 = new QLabel("Telephone 2");
    leftLayout->setWidget(7, QFormLayout::LabelRole, label_6);
    phonebisTxt = new QLineEdit(this);
    leftLayout->setWidget(7, QFormLayout::FieldRole, phonebisTxt);
    label_7 = new QLabel("Addresse");
    leftLayout->setWidget(8, QFormLayout::LabelRole, label_7);
    addrTxt = new QLineEdit(this);
    leftLayout->setWidget(8, QFormLayout::FieldRole, addrTxt);
    label_10 = new QLabel("Code");
    leftLayout->setWidget(9, QFormLayout::LabelRole, label_10);
    codeTxt = new QLineEdit(this);
    leftLayout->setWidget(9, QFormLayout::FieldRole, codeTxt);
    label_9 = new QLabel("Ville");
    leftLayout->setWidget(10, QFormLayout::LabelRole, label_9);
    villeTxt = new QLineEdit(this);
    leftLayout->setWidget(10, QFormLayout::FieldRole, villeTxt);
    label_8 = new QLabel("Pays");
    leftLayout->setWidget(11, QFormLayout::LabelRole, label_8);
    paysTxt = new QLineEdit(this);
    leftLayout->setWidget(11, QFormLayout::FieldRole, paysTxt);
    label_11 = new QLabel("Language");
    leftLayout->setWidget(12, QFormLayout::LabelRole, label_11);
    languageTxt = new QLineEdit(this);
    languageTxt->setObjectName(QString::fromUtf8("languageTxt"));
    leftLayout->setWidget(12, QFormLayout::FieldRole, languageTxt);
    activeBox = new QCheckBox("Active");
    activeBox->setObjectName(QString::fromUtf8("activeBox"));
    leftLayout->setWidget(0, QFormLayout::FieldRole, activeBox);
    rightLayout = new QFormLayout();
    rightLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    rightLayout->setHorizontalSpacing(4);
    rightLayout->setVerticalSpacing(10);
    graphicsView = new QGraphicsView(this);
    rightLayout->setWidget(2, QFormLayout::FieldRole, graphicsView);
    classTxt = new QLineEdit(this);
    classTxt->setObjectName(QString::fromUtf8("classTxt"));
    rightLayout->setWidget(0, QFormLayout::FieldRole, classTxt);
    label_5 = new QLabel("Classe");
    label_5->setObjectName(QString::fromUtf8("label_5"));
    rightLayout->setWidget(0, QFormLayout::LabelRole, label_5);
    lineEdit_7 = new QLineEdit(this);
    lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
    rightLayout->setWidget(3, QFormLayout::FieldRole, lineEdit_7);
    formLayout->addLayout(leftLayout);
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
    msgBox.setText("Confirmation de la modification");
    msgBox.setInformativeText("Confirmez vous la modification?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    if (ret == QMessageBox::Yes)
    {
        if (user == 0)
        {
        user->setName(nomTxt->text());
        user->setSurname(prenomTxt->text());
        user->setLanguage(languageTxt->text());
        user->setLevel(3);
        user->save();
        nomTxt->setText("");
        prenomTxt->setText("");
        languageTxt->setText("");
    }
    }
    return;
}
void    StudentsPage::cancelUser()
{
    QMessageBox msgBox;
    msgBox.setText("Confirmation de l'annulation");
    msgBox.setInformativeText("Etes-vous sur de vouloir annulé?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    if (ret == QMessageBox::Yes)
    {
        nomTxt->setText("");
        prenomTxt->setText("");
        languageTxt->setText("");
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
    data->setLevel(3);
        data->save();
    loginTxt->setText("");
    nomTxt->setText("");
    passTxt->setText("");
    prenomTxt->setText("");
    languageTxt->setText("");
    studentTree->setModel(new StudentModel(_users->getAllUser(), 1));
    msgBox.setText("The user was succefully created");
    msgBox.exec();
}
