#include "FileFram.h"

FileFram::FileFram(QWidget *parent) :
    QFrame(parent){
    setupUi(this);
}

void FileFram::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}
