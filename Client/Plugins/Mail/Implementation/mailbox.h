#ifndef MAILBOX_H
#define MAILBOX_H

#include <QtGui/QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QDebug>

namespace Ui
{
    class mailboxClass;
}

class mailbox : public QMainWindow
{
    Q_OBJECT

public:
    mailbox(QWidget *parent = 0);
    ~mailbox();

private:
    Ui::mailboxClass *ui;
    QString from;
    QString to;
    QString subject;
    QString content;

private slots:
    void new_message();
    void show_box();
    void hideall();
    void send_message();
};

#endif // MAILBOX_H
