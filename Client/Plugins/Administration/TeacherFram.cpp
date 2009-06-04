#include "TeacherFram.h"

TeacherFram::TeacherFram(INetwork *res) :
    QFrame(){
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
