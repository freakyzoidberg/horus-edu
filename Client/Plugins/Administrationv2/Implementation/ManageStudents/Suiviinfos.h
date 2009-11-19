#ifndef SUIVIINFOS_H
#define SUIVIINFOS_H

#include <QWidget>
#include <QFrame>
#include <QLineEdit>
#include <QSpinBox>
#include <QTextEdit>
#include <QGridLayout>
#include <QLabel>
#include "../../../../../Common/UserData.h"
class SuiviInfos : public QFrame
{
    public:
        SuiviInfos();
		SuiviInfos(UserData *d);

        QString     getSuivi() { return suivi->toPlainText(); }
        QString     getClassNextYear() { return ClasseNextYear->text(); }
    private:

        QTextEdit *suivi;
        QLineEdit *ClasseNextYear;
};

#endif // SUIVIINFOS_H
