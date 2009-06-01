#include "AdminFram.h"

AdminFram::AdminFram(QWidget *parent) : QWidget(parent)
{
    setupUi(this);
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
