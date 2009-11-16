#include "BasicInfos.h"

BasicInfos::BasicInfos()
{
    QFormLayout *BasicLayout = new QFormLayout(this);

    name = new QLineEdit(this);
    surname = new QLineEdit(this);
    bday = new QLineEdit(this);
    address = new QLineEdit(this);

    BasicLayout->addRow(tr("name"), name);
    BasicLayout->addRow(tr("surname"), surname);
    BasicLayout->addRow(tr("birthday"), bday);
    BasicLayout->addRow(tr("adress"), address);
    this->setLayout(BasicLayout);
}

BasicInfos::BasicInfos(UserData* ud)
{
    QFormLayout *BasicLayout = new QFormLayout(this);

    name = new QLineEdit(this);
    name->setText(ud->name());
    surname = new QLineEdit(this);
    surname->setText(ud->surname());
    bday = new QLineEdit(this);
    bday->setText(ud->birthDate().toString());
    address = new QLineEdit(this);
    address->setText(ud->address());

    BasicLayout->addRow(tr("name"), name);
    BasicLayout->addRow(tr("surname"), surname);
    BasicLayout->addRow(tr("birthday"), bday);
    BasicLayout->addRow(tr("adress"), address);
    this->setLayout(BasicLayout);
}
