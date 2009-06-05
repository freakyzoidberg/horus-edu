#include "UserFram.h"
#include "../../../Common/PluginPacket.h"
#include <QDebug>
#include <QMessageBox>
#include <QCryptographicHash>


UserFram::UserFram(INetwork *reseau, QObject *parent) : QFrame()
{
    res = reseau;
    this->parent = parent;
    setupUi(this);
    fillUserFram();
    requestFunctions["changePassword"]  = &UserFram::changePasswordResponse;
    requestFunctions["listUsers"]       = &UserFram::listUsersResponse;
    requestFunctions["getUserInfo"]     = &UserFram::getUserInfoResponse;
    requestFunctions["setUserInfo"]     = &UserFram::setUserInfoResponse;
    requestFunctions["createNewUser"]   = &UserFram::createNewUserResponse;
    requestFunctions["disableUser"]     = &UserFram::disableUserResponse;
    requestFunctions["getAllTree+"]         = &UserFram::getTreeResponse;
    requestFunctions["getNodeInfo"]     = &UserFram::getNodInfoResponse;
    requestFunctions["setNode"]         = &UserFram::editNodeResponse;
    connect(this, SIGNAL(sender(QString)), this->parent, SLOT(sender(QString)));
    connect(this->studentTree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(itemClicked(QTreeWidgetItem*, int)));
    this->SaveButton->hide();
    listUsers();
    this->getTree();
}

void    UserFram::fillUserFram()
{

    this->menuW->setLayout(this->menuLayout);
    this->formW->setLayout(this->formLayout);
    this->userLayout->setRowStretch(0, 1);
    this->userLayout->setRowStretch(1, 18);
    this->mainLayout->setColumnStretch(0, 1);
    this->mainLayout->setColumnStretch(1, 3);
    this->setLayout(this->mainLayout);
}

void    UserFram::on_AddButton_clicked()
{
    this->createNewUser();
}

void    UserFram::on_SaveButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Confirmation de la modification");
    msgBox.setInformativeText("Confirmez vous la modification?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    if (ret == QMessageBox::Yes)
        this->setUserInfo();
    return;
    qDebug() << "Save";
}

void    UserFram::on_DelButton_clicked()
{
    qDebug() << "Del";
}

void    UserFram::on_CancelButton_clicked()
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
    return;
    qDebug() << "Cancel";
}
void    UserFram::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}

void UserFram::itemClicked(QTreeWidgetItem *item, int idx)
{
    this->AddButton->hide();
    this->SaveButton->show();
    this->loginTxt->setText(this->studentlist[item->data(1, 0).toString()]["login"].toString());
    this->passTxt->setText(this->studentlist[item->data(1, 0).toString()]["password"].toString());
    this->addrTxt->setText(this->studentlist[item->data(1, 0).toString()]["address"].toString());
    this->phoneTxt->setText(this->studentlist[item->data(1, 0).toString()]["phone"].toString());
    this->paysTxt->setText(this->studentlist[item->data(1, 0).toString()]["country"].toString());
    this->languageTxt->setText(this->studentlist[item->data(1, 0).toString()]["language"].toString());
    this->prenomTxt->setText(this->studentlist[item->data(1, 0).toString()]["name"].toString());
    this->nomTxt->setText(this->studentlist[item->data(1, 0).toString()]["surname"].toString());
    this->date->setSelectedDate(this->studentlist[item->data(1, 0).toString()]["birth_day"].toDate());

    this->activeBox->setChecked(this->studentlist[item->data(1, 0).toString()]["enabled"].toBool());
    //qDebug() << this->studentlist[item->data(1, 0).toString()]["login"];
}

void    UserFram::listUsers()
{
    QVariantHash request;

    request["Request"] =  "listUsers";
    PluginPacket pP("UserManagment", request);
    this->res->sendPacket(pP);
    emit sender("students");
}

void    UserFram::getUserInfo()
{
    QVariantHash request;

    request["Request"] =  "getUserInfo";
}

void    UserFram::setUserInfo()
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
    request["password"] = QCryptographicHash::hash(this->passTxt->text().toUtf8(), QCryptographicHash::Sha1);;
    request["level"] = LEVEL_STUDENT;
    request["address"] = this->addrTxt->text();
    request["phone"] = this->phoneTxt->text();
    request["country"] = this->paysTxt->text();
    request["name"] = this->prenomTxt->text();
    request["surname"] = this->nomTxt->text();
    request["birth_day"] = this->date->selectedDate();
    request["picture"] = "vide";
    request["language"] = this->languageTxt->text();
    request["id_tree"] = "0";
    request["enabled"] = this->activeBox->isChecked();
    PluginPacket pP("UserManagment", request);
    emit sender("students");
    this->res->sendPacket(pP);
}

void    UserFram::createNewUser()
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
    request["level"] = LEVEL_STUDENT;
    request["name"] = this->prenomTxt->text();
    request["surname"] = this->nomTxt->text();
    request["birth_day"] = this->date->selectedDate();
    request["picture"] = "vide";
    request["address"] = this->addrTxt->text();
    request["phone"] = this->phoneTxt->text();
    request["country"] = this->paysTxt->text();
    request["language"] = this->languageTxt->text();
    request["id_tree"] = "0";
    request["enabled"] = this->activeBox->isChecked();
    PluginPacket pP("UserManagment", request);
    emit sender("students");
    this->res->sendPacket(pP);
    this->listUsers();
}

void    UserFram::disableUser()
{
    QVariantHash request;

    request["Request"] =  "disableUser";
    emit sender("students");
}

void    UserFram::readResponse(QVariantHash response)
{

    (this->*requestFunctions.value(response["Request"].toByteArray(),
                                   &UserFram::unknownResponse))
                                   (response);
}

void    UserFram::changePasswordResponse(QVariantHash &response)
{
    qDebug() << response;
}

void    UserFram::listUsersResponse(QVariantHash &response)
{
    if (response["Success"] == false)
        return;
    this->studentlist.clear();
    this->studentTree->clear();
    QTreeWidgetItem *students = new QTreeWidgetItem(this->studentTree);
    students->setText(0,"Etudiants");
    QVariantList list;
    list = response["Users"].toList();
    QList<QVariant>::iterator i;
    for (i = list.begin(); i != list.end(); ++i)
    {
        if (QVariant(*i).toHash()["level"] == LEVEL_STUDENT)
        {
            QTreeWidgetItem *itemTree = new QTreeWidgetItem(students);
            this->studentlist.insert(QVariant(*i).toHash()["id"].toString(), QVariant(*i).toHash());
            itemTree->setData(1,0, QVariant(*i).toHash()["id"].toString());
            itemTree->setText(0, QVariant(*i).toHash()["login"].toString());
        }
    }
}

void    UserFram::getUserInfoResponse(QVariantHash &response)
{
    qDebug() << response;
}

void    UserFram::setUserInfoResponse(QVariantHash &response)
{
    QMessageBox msgBox;
    QString msg;
    if (response["Success"] == true)
    {
        QString msg;
        msg.append("les infos de l'etudiant on ete modifié avec succes \n");
        QMessageBox msgBox;
        msgBox.setText(msg);
        msgBox.exec();
        clearForm();
        this->AddButton->show();
        this->SaveButton->hide();
        this->listUsers();
    }
    else
    {
        msg.append("la modification des infos a echoue \n");
        msgBox.setText(msg);
        msgBox.exec();
    }
    //qDebug() << response;
}

void    UserFram::createNewUserResponse(QVariantHash &response)
{
    QMessageBox msgBox;
    QString msg;
    if (response["Success"] == true)
    {
        msg.append("l'etudiant a ete rajoute avec succes \n");
        msgBox.setText(msg);
        msgBox.exec();
        this->AddButton->show();
        this->SaveButton->hide();
        clearForm();
    }
    else
    {
        msg.append("l'ajout de l'etudiant a echoue \n");
        msgBox.setText(msg);
        msgBox.exec();
    }
}

void    UserFram::clearForm()
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

void    UserFram::disableUserResponse(QVariantHash &response)
{
    qDebug() << response;
}


void    UserFram::unknownResponse(QVariantHash &response)
{
    qDebug() << response;
}
void    UserFram::updateTree(QVariantHash tree)
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

void    UserFram::getTree()
{
    QVariantHash request;
    request["Request"]=  "getAllTree+";

    PluginPacket pP("TreeManagement", request);
    emit sender("students");
    this->res->sendPacket(pP);
}

void    UserFram::getNodInfo()
{
    QVariantHash request;

    request["Request"] = "getNodeInfo";
    request["idNode"] = "";
}

void            UserFram::deleteNode(QString idNode)
{
    QVariantHash request;

    request["Request"] = "setNode";
    request["Admntreeact"] = "Delnode";
    request["Id"] = "";
}

void            UserFram::moveNode(QString from, QString to)
{
    QVariantHash request;

    request["Request"] = "setNode";
    request["Admntreeact"] = "Mvnode";
    request["Id"] = from;
    request["Newfather"] = to;
}

void            UserFram::editNode(QString id, QString type, QString name, QString userId)
{
    QVariantHash request;

    request["Request"] = "setNode";
    request["Admntreeact"] = "Addnode";
    request["Newfather"] = id;
    request["Type"] = type;
    request["Name"] = name;
    request["UserRef"] = userId;
}

void    UserFram::getTreeResponse(QVariantHash &response)
{
    QHash<QString, QVariant > usertree;
    usertree = response["AllTree"].toHash();
    for (QHash<QString, QVariant >::iterator it = usertree.begin(); it != usertree.end(); ++it)
    {
        qDebug() << "User Tree node :" << it.key();
        //tmplist = it.value().toList();
    }
}

void    UserFram::getNodInfoResponse(QVariantHash &response)
{
    qDebug() << response;
}

void    UserFram::editNodeResponse(QVariantHash &response)
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
