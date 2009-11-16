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
    QLineEdit *referent;
    QLineEdit *aides;
    QTextEdit *motif;
};

#endif // SOCIALINFOS_H
