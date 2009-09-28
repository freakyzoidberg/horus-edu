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
#include                        "../../../../Common/DataImplementations/MailData/MailDataPlugin.h"
//class MailPanel;
class MailPanel : public QWidget
{
    Q_OBJECT

public:
    MailPanel(MailDataPlugin *MailPlugin);
    ~MailPanel();

private:
    QHBoxLayout layout;
    MailList *Mlist;
    MailForm *Mform;
QVBoxLayout *contentright;
MailDataPlugin* _MailPlugin;
private slots:
        void changetowrite();
        void changetolist();


};

#endif // MAILPANEL_H
