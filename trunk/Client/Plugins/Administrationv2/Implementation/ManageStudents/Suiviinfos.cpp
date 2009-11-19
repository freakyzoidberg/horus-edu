#include "Suiviinfos.h"

SuiviInfos::SuiviInfos()
{
    setProperty("isFormFrame", true);
    QGridLayout *BasicLayout = new QGridLayout(this);

    BasicLayout->setMargin(8);
    BasicLayout->setSpacing(4);


    suivi = new QTextEdit();

    QLabel *label = new QLabel(tr("Suivi post ecoline"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 2, 0);
    BasicLayout->addWidget(suivi, 2, 1);
BasicLayout->setColumnMinimumWidth(0,150);
    this->setLayout(BasicLayout);
}

SuiviInfos::SuiviInfos(UserData *d)
{
    setProperty("isFormFrame", true);
    QGridLayout *BasicLayout = new QGridLayout(this);

    BasicLayout->setMargin(8);
    BasicLayout->setSpacing(4);
    suivi = new QTextEdit();
    suivi->setPlainText(d->followUp());



    QLabel *label = new QLabel(tr("Suivi post ecoline"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 2, 0);
    BasicLayout->addWidget(suivi, 2, 1);
    BasicLayout->setColumnMinimumWidth(0,150);
    this->setLayout(BasicLayout);
}
