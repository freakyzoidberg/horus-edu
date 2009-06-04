#include "ClassFram.h"

ClassFram::ClassFram(INetwork *res) :
    QFrame(){
    setupUi(this);
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
