#include "ClassFram.h"

ClassFram::ClassFram(INetwork *res) :
    QFrame()
{
    setupUi(this);
    this->mainLayout->setColumnStretch(0, 1);
    this->mainLayout->setColumnStretch(1, 3);
    this->setLayout(this->mainLayout);
}

void ClassFram::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}
