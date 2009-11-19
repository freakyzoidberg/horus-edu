#include "Schoolinfos.h"

SchoolInfos::SchoolInfos()
{
    setProperty("isFormFrame", true);
    QGridLayout *BasicLayout = new QGridLayout(this);


    nb_redoublement = new QSpinBox();
    nb_redoublement->setMaximumWidth(100);
    BasicLayout->setMargin(8);
    BasicLayout->setSpacing(4);

    QLabel* label = new QLabel(tr("Redoublement"));
    label->setProperty("isFormLabel", true);

    label->setMaximumWidth(150);
    label->setMinimumWidth(150);
    BasicLayout->addWidget(label, 0, 0,Qt::AlignLeft);
    BasicLayout->addWidget(nb_redoublement, 0, 1);

    annee_entree = new QSpinBox();
    annee_entree->setMinimum(1980);
    annee_entree->setValue(2010);
    annee_entree->setMaximum(3000);
    annee_entree->setMaximumWidth(100);
    label->setMinimumWidth(150);
            label = new QLabel(tr("Entry year"));
            label->setProperty("isFormLabel", true);
            label->setMaximumWidth(150);
            label->setMinimumWidth(150);
            BasicLayout->addWidget(label, 1, 0, Qt::AlignLeft);
            BasicLayout->addWidget(annee_entree, 1, 1);
BasicLayout->setColumnMinimumWidth(0,150);
    this->setLayout(BasicLayout);
}



SchoolInfos::SchoolInfos(UserData *d)
{
    setProperty("isFormFrame", true);
    QGridLayout *BasicLayout = new QGridLayout(this);
    BasicLayout->setMargin(8);
    BasicLayout->setSpacing(4);

    nb_redoublement = new QSpinBox();
    nb_redoublement->setValue(d->repeatedYears());
    nb_redoublement->setMaximumWidth(100);



    QLabel* label = new QLabel(tr("Redoublement"));
    label->setProperty("isFormLabel", true);
    label->setMaximumWidth(150);
    label->setMinimumWidth(150);
    BasicLayout->addWidget(label, 0, 0,Qt::AlignLeft);
    BasicLayout->addWidget(nb_redoublement, 0, 1);

    annee_entree = new QSpinBox();
    annee_entree->setMinimum(1980);
    annee_entree->setValue(2010);
    annee_entree->setMaximum(3000);
    annee_entree->setValue(d->startYear());

                QLabel* label2 = new QLabel(tr("Entry year"));
                label2->setProperty("isFormLabel", true);
                label2->setMaximumWidth(150);
                label2->setMinimumWidth(150);
                BasicLayout->addWidget(label2, 1, 0, Qt::AlignLeft);
                BasicLayout->addWidget(annee_entree, 1, 1);

    BasicLayout->setColumnMinimumWidth(0,150);
    this->setLayout(BasicLayout);
}
