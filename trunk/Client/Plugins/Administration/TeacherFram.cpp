#include "TeacherFram.h"
#include "../../../Common/PluginPacket.h"
#include <QDebug>
#include <QMessageBox>
#include <QCryptographicHash>

TeacherFram::TeacherFram(INetwork *res, QObject     *parent) :
    QFrame()
{
    this->res = res;
    this->parent = parent;
    setupUi(this);

    fillTeacherFram();
    requestFunctions["changePassword"]  = &TeacherFram::changePasswordResponse;
    requestFunctions["listUsers"]       = &TeacherFram::listUsersResponse;
    requestFunctions["getUserInfo"]     = &TeacherFram::getUserInfoResponse;
    requestFunctions["setUserInfo"]     = &TeacherFram::setUserInfoResponse;
    requestFunctions["createNewUser"]   = &TeacherFram::createNewUserResponse;
    requestFunctions["disableUser"]     = &TeacherFram::disableUserResponse;
    connect(this->profTree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(itemClicked(QTreeWidgetItem*, int)));
    connect(this, SIGNAL(sender(QString)), this->parent, SLOT(sender(QString)));
}

void    TeacherFram::fillTeacherFram()
{
    this->menuW->setLayout(this->menuLayout);
    this->formW->setLayout(this->formLayout);
    this->userLayout->setRowStretch(0, 1);
    this->userLayout->setRowStretch(1, 18);
    this->mainLayout->setColumnStretch(0, 1);
    this->mainLayout->setColumnStretch(1, 3);
    this->setLayout(this->mainLayout);
}


void TeacherFram::itemClicked(QTreeWidgetItem *item, int idx)
{
    this->AddButton->hide();
    this->SaveButton->show();
    this->loginTxt->setText(this->proflist[item->data(1, 0).toString()]["login"].toString());
    this->passTxt->setText(this->proflist[item->data(1, 0).toString()]["password"].toString());
    this->addrTxt->setText(this->proflist[item->data(1, 0).toString()]["address"].toString());
    this->phoneTxt->setText(this->proflist[item->data(1, 0).toString()]["phone"].toString());
    this->paysTxt->setText(this->proflist[item->data(1, 0).toString()]["country"].toString());
    this->languageTxt->setText(this->proflist[item->data(1, 0).toString()]["language"].toString());
    this->prenomTxt->setText(this->proflist[item->data(1, 0).toString()]["name"].toString());
    this->nomTxt->setText(this->proflist[item->data(1, 0).toString()]["surname"].toString());
    this->date->setSelectedDate(this->proflist[item->data(1, 0).toString()]["birth_day"].toDate());
    this->activeBox->setChecked(this->proflist[item->data(1, 0).toString()]["language"].toBool());
}

void    TeacherFram::on_AddButton_clicked()
{
    this->createNewUser();
}

void    TeacherFram::on_SaveButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Confirmation de l'annulation");
    msgBox.setInformativeText("Etes-vous sur de vouloir annulé?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    if (ret == QMessageBox::Yes)
        this->setUserInfo();
    qDebug() << "Save";
    return;
}

void    TeacherFram::on_DelButton_clicked()
{
    qDebug() << "Del";
}

void    TeacherFram::on_CancelButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Confirmation de l'annulation");
    msgBox.setInformativeText("Etes-vous sur de vouloir annulé?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    if (ret == QMessageBox::Yes)
    {
        this->AddButton->show();
        this->SaveButton->hide();
        this->clearForm();
    }

    qDebug() << "Cancel";
    return;
}
void    TeacherFram::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}

void    TeacherFram::changePassword()
{
    QVariantHash request;

    request["Request"] =  "changePassword";
    request["password"] =  "";
    request["OldPassword"]=  "";
}

void    TeacherFram::listUsers()
{
    QVariantHash request;

    request["Request"] =  "listUsers";
    PluginPacket pP("UserManagment", request);
    this->res->sendPacket(pP);

}

void    TeacherFram::getUserInfo()
{
    QVariantHash request;

    request["Request"] =  "getUserInfo";
}

void    TeacherFram::setUserInfo()
{
    QVariantHash request;
    QString      Error = "";

    request["Request"] =  "setUserInfo";
    if(this->loginTxt->text() == "")
        Error.append("Login |");
    if(this->passTxt->text() == "")
        Error.append("Password |");
    if(this->addrTxt->text() == "")
        Error.append("Adresse |");
    if(this->phoneTxt->text() == "")
        Error.append("Telephone |");
    if(this->paysTxt->text() == "")
        Error.append("Pays |");
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
        QMessageBox msgBox;
        msgBox.setText(msg);
        msgBox.exec();
        return;
    }
    request["login"] = this->loginTxt->text();
    request["password"] = QCryptographicHash::hash(this->passTxt->text().toUtf8(), QCryptographicHash::Sha1).toHex();
    request["level"] = LEVEL_TEACHER;
    request["address"] = this->addrTxt->text();
    request["phone"] = this->phoneTxt->text();
    request["name"] = this->prenomTxt->text();
    request["surname"] = this->nomTxt->text();
    request["birth_day"] = this->date->selectedDate();
    request["picture"] = "vide";
    request["country"] = this->paysTxt->text();
    request["language"] = this->languageTxt->text();
    request["id_tree"] = "9";
    request["enabled"] = this->activeBox->isChecked();
    PluginPacket pP("UserManagment", request);
    emit sender("profs");
    this->res->sendPacket(pP);
}

void    TeacherFram::createNewUser()
{
    QVariantHash request;
    QString      Error = "";

    request["Request"] =  "createNewUser";
    if(this->loginTxt->text() == "")
        Error.append("Login |");
    if(this->passTxt->text() == "")
        Error.append("Password |");
    if(this->addrTxt->text() == "")
        Error.append("Adresse |");
    if(this->phoneTxt->text() == "")
        Error.append("Telephone |");
    if(this->paysTxt->text() == "")
        Error.append("Pays |");
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
        QMessageBox msgBox;
        msgBox.setText(msg);
        msgBox.exec();
        return;
    }
    request["login"] = this->loginTxt->text();
    request["password"] = QCryptographicHash::hash(this->passTxt->text().toUtf8(), QCryptographicHash::Sha1).toHex();
    request["level"] = LEVEL_TEACHER;
    request["address"] = this->addrTxt->text();
    request["phone"] = this->phoneTxt->text();
    request["name"] = this->prenomTxt->text();
    request["surname"] = this->nomTxt->text();
    request["birth_day"] = this->date->selectedDate();
    request["picture"] = "vide";
    request["country"] = this->paysTxt->text();
    request["language"] = this->languageTxt->text();
    request["id_tree"] = "9";
    request["enabled"] = this->activeBox->isChecked();
    PluginPacket pP("UserManagment", request);
    emit sender("profs");
    this->res->sendPacket(pP);
    this->listUsers();
}

void    TeacherFram::disableUser()
{
    QVariantHash request;

    request["Request"] =  "disableUser";
}

void    TeacherFram::readResponse(QVariantHash response)
{
    (this->*requestFunctions.value(response["Request"].toByteArray(),
                                   &TeacherFram::unknownResponse))
                                   (response);
}

void    TeacherFram::unknownResponse(QVariantHash &response)
{
    qDebug() << response;
}

void    TeacherFram::changePasswordResponse(QVariantHash &response)
{
    qDebug() << response;
}

void    TeacherFram::listUsersResponse(QVariantHash &response)
{
    if (response["Success"] == false)
        return;
    QTreeWidgetItem *profs = new QTreeWidgetItem(this->profTree);
    profs->setText(0,"Etudiants");
    QVariantList list;
    list = response["Users"].toList();
    QList<QVariant>::iterator i;
    this->proflist.clear();
    //this->profTree->clear();
    for (i = list.begin(); i != list.end(); ++i)
    {
        if (QVariant(*i).toHash()["level"] == LEVEL_TEACHER)
        {
            QTreeWidgetItem *itemTree = new QTreeWidgetItem(profs);
            this->proflist.insert(QVariant(*i).toHash()["id"].toString(), QVariant(*i).toHash());
            itemTree->setData(1,0, QVariant(*i).toHash()["id"].toString());
            itemTree->setText(0, QVariant(*i).toHash()["login"].toString());
        }
    }
}

void    TeacherFram::getUserInfoResponse(QVariantHash &response)
{
    qDebug() << response;
}

void    TeacherFram::setUserInfoResponse(QVariantHash &response)
{
    QMessageBox msgBox;
    QString msg;
    if (response["Success"] == true)
    {

        msg.append("les infos du professeur ont ete modifié avec succes \n");
        msgBox.setText(msg);
        msgBox.exec();
        clearForm();
        this->AddButton->show();
        this->SaveButton->hide();
    }
    else
    {
        msg.append("la modification des infos a echoue \n");
        msgBox.setText(msg);
        msgBox.exec();
    }
}

void    TeacherFram::createNewUserResponse(QVariantHash &response)
{
    QMessageBox msgBox;
    QString msg;
    if (response["Success"] == true)
    {
        QString msg;
        msg.append("le professeur a ete rajoute avec succes \n");
        msgBox.setText(msg);
        msgBox.exec();
        clearForm();
        this->AddButton->show();
        this->SaveButton->hide();
    }
    else
    {
        msg.append("l'ajout de l'utilisateur a echoue \n");
        msgBox.setText(msg);
        msgBox.exec();
    }
}

void    TeacherFram::clearForm()
{
    this->loginTxt->setText("");
    this->addrTxt->setText("");
    this->phoneTxt->setText("");
    this->languageTxt->setText("");
    this->passTxt->setText("");
    this->phonebisTxt->setText("");
    this->nomTxt->setText("");
    this->prenomTxt->setText("");
    this->codeTxt->setText("");
    this->paysTxt->setText("");
    this->languageTxt->setText("");
    this->villeTxt->setText("");
    this->activeBox->setChecked(false);
}

void    TeacherFram::disableUserResponse(QVariantHash &response)
{
    qDebug() << response;
}

void    TeacherFram::updateTree(QVariantHash tree)
{
   /* for (QHash<QString, QVariant >::const_iterator it = usertree.begin(); it != usertree.end(); ++it)
    {
        qDebug() << "User Tree node :" << it.key();
        tmplist = it.value().toList();
       for (int i = 0; i < tmplist.size(); ++i)
        {
          qDebug() << " sons :" << (tmplist.value(i));
        }
    }*/
    //build index
}

void    TeacherFram::getTree()
{
    QVariantHash request;
    request["Request"]=  "getTree";

    /*QTreeWidgetItem *cours1 = new QTreeWidgetItem(this);
    cours1->setText(0,"cours 1");

    //build child
    QTreeWidgetItem *lesson1 = new QTreeWidgetItem(cours1);
    lesson1->setText(0,"lesson 1");

    QTreeWidgetItem *cours2 = new QTreeWidgetItem;
    cours2->setText(0,"cours 2");

    this->insertTopLevelItem(0, cours1);
    this->insertTopLevelItem(1, cours2);*/
    //this->show();
}

void    TeacherFram::getNodInfo()
{
    QVariantHash request;

    request["Request"] = "getNodeInfo";
    request["idNode"] = "";
}

void            TeacherFram::deleteNode(QString idNode)
{
    QVariantHash request;

    request["Request"] = "setNode";
    request["Admntreeact"] = "Delnode";
    request["Id"] = "";
}

void            TeacherFram::moveNode(QString from, QString to)
{
    QVariantHash request;

    request["Request"] = "setNode";
    request["Admntreeact"] = "Mvnode";
    request["Id"] = from;
    request["Newfather"] = to;
}

void            TeacherFram::editNode(QString id, QString type, QString name, QString userId)
{
    QVariantHash request;

    request["Request"] = "setNode";
    request["Admntreeact"] = "Addnode";
    request["Newfather"] = id;
    request["Type"] = type;
    request["Name"] = name;
    request["UserRef"] = userId;
}

void    TeacherFram::getTreeResponse(QVariantHash &response)
{
    qDebug() << response;
}

void    TeacherFram::getNodInfoResponse(QVariantHash &response)
{
    qDebug() << response;
}

void    TeacherFram::editNodeResponse(QVariantHash &response)
{
    if (response["Admntreeact"] == "Addnode")
    {

    }
    else if (response["Admntreeact"] == "Mvnode")
    {

    }
    else if (response["Admntreeact"] == "Delnode")
    {

    }
}
