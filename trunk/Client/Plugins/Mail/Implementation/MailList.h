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
    //QTableView *emailList;

/*
private slots:
    void myClicked(QModelIndex);
  */

    void setSourceModel(QAbstractItemModel *model);

private slots:
    void filterRegExpChanged();
    void filterColumnChanged();
    void sortChanged();
    void rowDoubleClicked(QModelIndex indx);

private:
    QTextEdit *mailview;
    QStandardItemModel *model;
    QSortFilterProxyModel *proxyModel;
    QGroupBox *sourceGroupBox;
    QGroupBox *proxyGroupBox;
    QTreeView *sourceView;
    QTreeView *proxyView;
    QCheckBox *filterCaseSensitivityCheckBox;
    QCheckBox *sortCaseSensitivityCheckBox;
    QLabel *filterPatternLabel;
    QLabel *filterSyntaxLabel;
    QLabel *filterColumnLabel;
    QLineEdit *filterPatternLineEdit;
    QComboBox *filterSyntaxComboBox;
    QComboBox *filterColumnComboBox;
    void addMail(QAbstractItemModel *model, const QString &subject, const QString &sender, const QDateTime &date, const QString &content, const QString &id);
    QAbstractItemModel *createMailModel(QObject *parent);
    QMap<QString, QString> mailpool;
};

#endif // MAILPANEL_H
