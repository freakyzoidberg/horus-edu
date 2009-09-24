#ifndef MAILPANEL_H
#define MAILPANEL_H

#include <QtGui/QWidget>
#include <QListWidget>
#include <QStackedWidget>
#include <QtGui>
#include <QGridLayout>

//class MailPanel;
class MailPanel : public QWidget
{
    Q_OBJECT

public:
    MailPanel();
    ~MailPanel();

private:
    QGridLayout layout;

};

#endif // MAILPANEL_H
