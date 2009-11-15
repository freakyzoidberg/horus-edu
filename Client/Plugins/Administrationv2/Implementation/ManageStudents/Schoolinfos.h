#ifndef SCHOOLINFOS_H
#define SCHOOLINFOS_H

#include <QWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QTextEdit>
#include <QGridLayout>
#include <QLabel>
class SchoolInfos : public QWidget
{
public:
    SchoolInfos();
    QLineEdit *raisons_renoublement;
    QSpinBox *nb_redoublement;
    QTextEdit *motif;
    QLineEdit *moyenne;
    QTextEdit *comment;
};

#endif // SCHOOLINFOS_H
