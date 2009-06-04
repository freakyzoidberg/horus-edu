#include "TeacherFram.h"

TeacherFram::TeacherFram(QWidget *parent) :
    QFrame(parent){
    setupUi(this);
}

void TeacherFram::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}
