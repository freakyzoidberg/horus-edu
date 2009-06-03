#include "TreeFram.h"

TreeFram::TreeFram(QWidget *parent) : QFrame(parent)
{
    setupUi(this);
}

void TreeFram::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}
