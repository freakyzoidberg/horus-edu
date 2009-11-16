#include "BasicInfos.h"

BasicInfos::BasicInfos()
{
//    QFormLayout *BasicLayout = new QFormLayout(this);
    setProperty("isFormFrame", true);
    QGridLayout *BasicLayout = new QGridLayout(this);
    BasicLayout->setMargin(8);
    BasicLayout->setSpacing(4);
    name = new QLineEdit(this);
    surname = new QLineEdit(this);
    bday = new QDateEdit(this);
    bday->setDisplayFormat("dd/MM/yy");
    QDate *now = new QDate();
    bday->setDate(now->currentDate());
    bday->setCalendarPopup(true);
    address = new QLineEdit(this);

    QLabel *label;

    label = new QLabel(tr("Nom"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 0, 0);
    BasicLayout->addWidget(name, 0, 1);

    //BasicLayout->addRow(tr("Nom"), name);

    label = new QLabel(tr("Surname"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 1, 0);
    BasicLayout->addWidget(surname, 1, 1);
    //BasicLayout->addRow(tr("Prenom"), surname);

    label = new QLabel(tr("Birthday"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 2, 0);
    BasicLayout->addWidget(bday, 2, 1);
    //BasicLayout->addRow(tr("Date de naissance"), bday);

    label = new QLabel(tr("Address"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 3, 0);
    BasicLayout->addWidget(address, 3, 1);
    //BasicLayout->addRow(tr("Adresse"), address);

    BasicLayout->setColumnMinimumWidth(0,150);
    this->setLayout(BasicLayout);
}

BasicInfos::BasicInfos(UserData* ud)
{
QGridLayout *BasicLayout = new QGridLayout(this);

    name = new QLineEdit(this);
    name->setText(ud->name());
    surname = new QLineEdit(this);
    surname->setText(ud->surname());
    bday = new QDateEdit(this);
    bday->setDisplayFormat("dd/MM/yy");
    bday->setCalendarPopup(true);
    QDate *now = new QDate();
    bday->setDate(now->currentDate());
    bday->setDate(ud->birthDate());
    address = new QLineEdit(this);
    address->setText(ud->address());









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