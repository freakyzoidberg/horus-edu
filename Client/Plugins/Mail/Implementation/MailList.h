#ifndef MAILLIST_H
#define MAILLIST_H

#include <QtGui/QWidget>
#include <QListWidget>
#include <QStackedWidget>
#include <QtGui>
#include <QListView>
#include                        "../../../../Common/DataImplementations/MailData/MailDataPlugin.h"
#include "MailAbstractModel.h"
#include "TextBrowser.h"
#include "MailPanel.h"

class				MailPanel;
//class MailList;
class MailList : public QWidget
{
     Q_OBJECT
public:
    MailList(MailDataPlugin *MailPlugin, MailPanel *panel);
    ~MailList();

private:
    MailDataPlugin *_MailPlugin;
    void setmailvisible(bool state);
    void setSourceModel(QAbstractItemModel *model);
    void addMail(QAbstractItemModel *model, const QString &subject, const QString &sender, const QDateTime &date, const QString &content, const QString &id);

private slots:
    void rowDoubleClicked(QModelIndex indx);
    void linkclick(const QString &link);
    void expandshrink();
    void reply();
    void replyall();

private:
    bool expanded;
    QString current;
    MailPanel *_panel;
    QList<MailData*> list;
    TextBrowser *mailview;
    QLineEdit *to_edit;
    QLineEdit *cc_edit;
    QLineEdit *sub_edit;
    QPushButton *maxi;
    QPushButton *rep;
    QPushButton *repall;
    QLabel *lto_edit;
    QLabel *lcc_edit;
    QStandardItemModel *model;
    QSortFilterProxyModel *proxyModel;
    QTreeView *proxyView;
    QAbstractItemModel *createMailModel(QObject *parent);
    QMap<QString, QString> mailpool;
};

#endif // MAILPANEL_H
