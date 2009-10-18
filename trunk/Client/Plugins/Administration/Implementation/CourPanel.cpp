#include "CourPanel.h"


CourPanel::CourPanel(QString cName)
{
    setupUi(cName);
}

void    CourPanel::setupUi(QString cName)
{
    courLayout = new QHBoxLayout(this);
    checkBoxs = new QVBoxLayout();
    coursName = new QLabel(cName);
    courLayout->addWidget(coursName);
    absenceCheck = new QCheckBox("Absence");
    checkBoxs->addWidget(absenceCheck);
    lateCheck = new QCheckBox("Retard");
    checkBoxs->addWidget(lateCheck);
    courLayout->addLayout(checkBoxs);
}
