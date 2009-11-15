#ifndef SOCIALINFOS_H
#define SOCIALINFOS_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QGridLayout>
#include <QLabel>
class SocialInfos : public QWidget
{
public:
    SocialInfos();
    QLineEdit *referent;
    QLineEdit *aides;
    QTextEdit *motif;
};

#endif // SOCIALINFOS_H
