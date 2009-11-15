#ifndef SUIVIINFOS_H
#define SUIVIINFOS_H

#include <QWidget>
#include <QWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QTextEdit>
#include <QGridLayout>
#include <QLabel>

class SuiviInfos : public QWidget
{
public:
    SuiviInfos();
    QSpinBox *annee_quitte;
    QTextEdit *suivi;
    QLineEdit *ClasseNextYear;



};

#endif // SUIVIINFOS_H
