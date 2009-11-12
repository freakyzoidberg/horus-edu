#include "CourPanel.h"


CourPanel::CourPanel(QString cName)
{
    setupUi(cName);
    connect(absenceCheck, SIGNAL(stateChanged(int)), this, SLOT(absChecked(int)));
    connect(lateCheck, SIGNAL(stateChanged(int)), this, SLOT(retardChecked(int)));
}

void    CourPanel::setupUi(QString cName)
{
    this->setMaximumSize(1000, 55);
    courLayout = new QHBoxLayout(this);
    checkBoxs = new QVBoxLayout();
    nameBoxs = new QVBoxLayout();
    coursName = new QLabel(cName);
    nameBoxs->addWidget(coursName, 1, Qt::AlignLeft);
    courLayout->addLayout(nameBoxs, 2);
    absenceCheck = new QCheckBox("Absence");
    checkBoxs->addWidget(absenceCheck, 1, Qt::AlignLeft);
    lateCheck = new QCheckBox("Retard");
    checkBoxs->addWidget(lateCheck, 1, Qt::AlignLeft);
    courLayout->addLayout(checkBoxs, 1);
}

void    CourPanel::retardChecked(int state)
{

}

void    CourPanel::absChecked(int state)
{

}
