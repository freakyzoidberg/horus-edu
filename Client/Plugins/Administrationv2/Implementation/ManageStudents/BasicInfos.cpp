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
    bday->setDisplayFormat(tr("dd/MM/yy"));
	bday->setDate(QDate::currentDate());
    bday->setCalendarPopup(true);
    address = new QLineEdit(this);

    QLabel *label;

    label = new QLabel(tr("Last name"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 0, 0);
    BasicLayout->addWidget(name, 0, 1);

    //BasicLayout->addRow(tr("Nom"), name);

    label = new QLabel(tr("First name"));
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

    setProperty("isFormFrame", true);
    BasicLayout->setMargin(8);
    BasicLayout->setSpacing(4);
    name = new QLineEdit(this);
    name->setText(ud->name());
    surname = new QLineEdit(this);
    surname->setText(ud->surname());
    bday = new QDateEdit(this);
    bday->setDisplayFormat(tr("dd/MM/yy"));
    bday->setCalendarPopup(true);
	bday->setDate(QDate::currentDate());
    bday->setDate(ud->birthDate());
    address = new QLineEdit(this);
    address->setText(ud->address());









    QLabel *label;

    label = new QLabel(tr("Last name"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 0, 0);
    BasicLayout->addWidget(name, 0, 1);

    //BasicLayout->addRow(tr("Nom"), name);

    label = new QLabel(tr("First name"));
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
