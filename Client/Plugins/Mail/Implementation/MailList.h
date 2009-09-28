#ifndef MAILLIST_H
#define MAILLIST_H

#include <QtGui/QWidget>
#include <QListWidget>
#include <QStackedWidget>
#include <QtGui>
#include <QListView>
#include                        "../../../../Common/DataImplementations/MailData/MailDataPlugin.h"
//class MailList;
class MailList : public QListView
{

public:
    MailList(MailDataPlugin *MailPlugin);
    ~MailList();


};

#endif // MAILPANEL_H
