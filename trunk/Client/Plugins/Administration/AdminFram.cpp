#include "AdminFram.h"

AdminFram::AdminFram(QWidget *parent) : QWidget(parent)
{
    setupUi(this);
    tF = new TreeFram(this);
    this->mainLayout->addWidget(tF, 0,0);
}

void AdminFram::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}
