#include "BasicInfos.h"

BasicInfos::BasicInfos()
{
//    QFormLayout *BasicLayout = new QFormLayout(this);
    QGridLayout *BasicLayout = new QGridLayout(this);
    name = new QLineEdit(this);
    surname = new QLineEdit(this);
    bday = new QDateEdit(this);
    address = new QLineEdit(this);

    BasicLayout->addWidget(new QLabel(tr("Nom")), 0, 0);
    BasicLayout->addWidget(name, 0, 1);

    //BasicLayout->addRow(tr("Nom"), name);

    BasicLayout->addWidget(new QLabel(tr("Surname")), 1, 0);
    BasicLayout->addWidget(surname, 1, 1);
    //BasicLayout->addRow(tr("Prenom"), surname);


    BasicLayout->addWidget(new QLabel(tr("Birthday")), 2, 0);
    BasicLayout->addWidget(bday, 2, 1);
    //BasicLayout->addRow(tr("Date de naissance"), bday);

    BasicLayout->addWidget(new QLabel(tr("Address")), 3, 0);
    BasicLayout->addWidget(address, 3, 1);
    //BasicLayout->addRow(tr("Adresse"), address);

    BasicLayout->setColumnMinimumWidth(0,150);
    this->setLayout(BasicLayout);
}

BasicInfos::BasicInfos(UserData* ud)
{
    QFormLayout *BasicLayout = new QFormLayout(this);

    name = new QLineEdit(this);
    name->setText(ud->name());
    surname = new QLineEdit(this);
    surname->setText(ud->surname());
    bday = new QDateEdit(this);
    bday->setDate(ud->birthDate());
    address = new QLineEdit(this);
    address->setText(ud->address());

    BasicLayout->addRow(tr("Nom"), name);
    BasicLayout->addRow(tr("Prenom"), surname);
    BasicLayout->addRow(tr("Date de naissance"), bday);
    BasicLayout->addRow(tr("Adresse"), address);
    this->setLayout(BasicLayout);
}
