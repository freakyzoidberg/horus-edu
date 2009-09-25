#ifndef MAILPANEL_H
#define MAILPANEL_H

#include <QtGui/QWidget>
#include <QListWidget>
#include <QStackedWidget>
#include <QtGui>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "MailList.h"
#include "MailForm.h"
//class MailPanel;
class MailPanel : public QWidget
{
    Q_OBJECT

public:
    MailPanel();
    ~MailPanel();

private:
    QHBoxLayout layout;
    MailList *Mlist;
    MailForm *Mform;
QVBoxLayout *contentright;

private slots:
        void changetowrite();
        void changetolist();


};

#endif // MAILPANEL_H
