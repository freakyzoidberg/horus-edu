#include "ClassFram.h"

ClassFram::ClassFram(QWidget *parent) :
    QFrame(parent){
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
