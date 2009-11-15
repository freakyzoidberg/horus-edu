#include "BasicInfos.h"

BasicInfos::BasicInfos()
{
    QFormLayout *BasicLayout = new QFormLayout(this);

    name = new QLineEdit(this);
    surname = new QLineEdit(this);
    bday = new QLineEdit(this);

    BasicLayout->addRow(tr("name"), name);
    BasicLayout->addRow(tr("surname"), surname);
    BasicLayout->addRow(tr("birthday"), bday);

    this->setLayout(BasicLayout);
}
