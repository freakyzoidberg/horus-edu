#ifndef SCHOOLINFOS_H
#define SCHOOLINFOS_H

#include <QFrame>
#include <QLineEdit>
#include <QSpinBox>
#include <QTextEdit>
#include <QGridLayout>
#include <QLabel>
#include "../../../../../Common/UserData.h"
class SchoolInfos : public QFrame
{
    public:
        SchoolInfos();
		SchoolInfos(UserData *d);
        QString     getMotif() { return motif->toPlainText(); }
        QString     getMoyenne() { return moyenne->text(); }
        QString     getComment() { return comment->toPlainText(); }
        int         getNb_red() { return nb_redoublement->value(); }
        //QString     getRaison() { return raisons_redoublement->text(); }
    private:
       // QLineEdit *raisons_redoublement;
        QSpinBox *nb_redoublement;
         QSpinBox *annee_entree;
        QTextEdit *motif;
        QLineEdit *moyenne;
        QTextEdit *comment;
};

#endif // SCHOOLINFOS_H
