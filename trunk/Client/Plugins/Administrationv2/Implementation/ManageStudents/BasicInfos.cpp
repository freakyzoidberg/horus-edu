#include "BasicInfos.h"

BasicInfos::BasicInfos()
{
    QFormLayout *BasicLayout = new QFormLayout(this);

    name = new QLineEdit(this);
    surname = new QLineEdit(this);
    bday = new QDateEdit(this);
    address = new QLineEdit(this);

    BasicLayout->addRow(tr("Nom"), name);
    BasicLayout->addRow(tr("Prenom"), surname);
    BasicLayout->addRow(tr("Date de naissance"), bday);
    BasicLayout->addRow(tr("Adresse"), address);
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
