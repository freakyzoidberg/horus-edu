#include "Suiviinfos.h"

SuiviInfos::SuiviInfos()
{
    setProperty("isFormFrame", true);
    QGridLayout *BasicLayout = new QGridLayout(this);

    BasicLayout->setMargin(8);
    BasicLayout->setSpacing(4);

    annee_quitte = new QSpinBox();
    suivi = new QTextEdit();
    //ClasseNextYear = new QLineEdit();
    annee_quitte->setMinimum(1980);
    annee_quitte->setValue(2010);
    annee_quitte->setMaximum(3000);
    //BasicLayout->addWidget(new QLabel(tr("Class next year")), 0, 0);
    //BasicLayout->addWidget(ClasseNextYear, 0, 1);

    QLabel* label = new QLabel(tr("Annee quitte"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 1, 0);
    BasicLayout->addWidget(annee_quitte, 1, 1);

    label = new QLabel(tr("Suivi post ecoline"));
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

    annee_quitte = new QSpinBox();
    annee_quitte->setMinimum(1980);
    annee_quitte->setMaximum(2080);
    annee_quitte->setValue(d->leaveYear());
    suivi = new QTextEdit();
    suivi->setPlainText(d->followUp());
    qDebug() << d->followUp();

    //ClasseNextYear = new QLineEdit();
    //BasicLayout->addWidget(new QLabel(tr("class next year")), 0, 0);
    //BasicLayout->addWidget(ClasseNextYear, 0, 1);

    QLabel* label = new QLabel(tr("Annee quitte"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 1, 0);
    BasicLayout->addWidget(annee_quitte, 1, 1);

    label = new QLabel(tr("Suivi post ecoline"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 2, 0);
    BasicLayout->addWidget(suivi, 2, 1);
BasicLayout->setColumnMinimumWidth(0,150);
    this->setLayout(BasicLayout);
}
