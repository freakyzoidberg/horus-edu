#include "SalleFram.h"

SalleFram::SalleFram(INetwork *res) :
    QFrame(){
    setupUi(this);
}

void SalleFram::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}
