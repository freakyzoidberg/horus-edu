#include "FileFram.h"

FileFram::FileFram(INetwork *res) : QFrame()
{
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
