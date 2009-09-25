#ifndef MAILPANEL_H
#define MAILPANEL_H

#include <QtGui/QWidget>
#include <QListWidget>
#include <QStackedWidget>
#include <QtGui>
#include <QVBoxLayout>
#include <QHBoxLayout>
//class MailPanel;
class MailPanel : public QWidget
{
    Q_OBJECT

public:
    MailPanel();
    ~MailPanel();

private:
    QHBoxLayout layout;

};

#endif // MAILPANEL_H
