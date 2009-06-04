#include "SalleFram.h"

SalleFram::SalleFram(QWidget *parent) :
    QFrame(parent){
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
