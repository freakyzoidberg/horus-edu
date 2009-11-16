#ifndef SOCIALINFOS_H
#define SOCIALINFOS_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QGridLayout>
#include <QLabel>
#include "../../../../../Common/UserData.h"
class SocialInfos : public QWidget
{
    public:
        SocialInfos();
		SocialInfos(UserData *d);
        QString     getMotif() { return motif->toPlainText(); }
        QString     getReferent() { return referent->text(); }
        QString     getAides() { return aides->text(); }
    private:
        QLineEdit *referent;
        QLineEdit *aides;
        QTextEdit *motif;
};

#endif // SOCIALINFOS_H
