#ifndef SCHOOLINFOS_H
#define SCHOOLINFOS_H

#include <QWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QTextEdit>
#include <QGridLayout>
#include <QLabel>
#include "../../../../../Common/UserData.h"
class SchoolInfos : public QWidget
{
public:
    SchoolInfos();
    SchoolInfos(UserData *d);
    QLineEdit *raisons_renoublement;
    QSpinBox *nb_redoublement;
    QTextEdit *motif;
    QLineEdit *moyenne;
    QTextEdit *comment;
};

#endif // SCHOOLINFOS_H
