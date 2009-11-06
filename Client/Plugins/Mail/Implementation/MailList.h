#ifndef MAILLIST_H
#define MAILLIST_H

#include <QtGui/QWidget>
#include <QListWidget>
#include <QStackedWidget>
#include <QtGui>
#include <QListView>
#include                        "../../../../Common/DataImplementations/MailData/MailDataPlugin.h"
#include "MailAbstractModel.h"

//class MailList;
class MailList : public QWidget
{
     Q_OBJECT
public:
    MailList(MailDataPlugin *MailPlugin);
    ~MailList();

private:
    MailDataPlugin *_MailPlugin;
    QTableView *emailList;

 private slots:
    void myClicked(QModelIndex);
};

#endif // MAILPANEL_H
