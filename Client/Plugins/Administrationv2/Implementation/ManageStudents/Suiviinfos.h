#ifndef SUIVIINFOS_H
#define SUIVIINFOS_H

#include <QWidget>
#include <QWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QTextEdit>
#include <QGridLayout>
#include <QLabel>
#include "../../../../../Common/UserData.h"
class SuiviInfos : public QWidget
{
    public:
        SuiviInfos();
		SuiviInfos(UserData *d);
        int         getLeftYear() { return annee_quitte->value(); }
        QString     getSuivi() { return suivi->toPlainText(); }
        QString     getClassNextYear() { return ClasseNextYear->text(); }
    private:
        QSpinBox *annee_quitte;
        QTextEdit *suivi;
        QLineEdit *ClasseNextYear;
};

#endif // SUIVIINFOS_H
