#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QtGui/QWidget>
#include "ui_LoginDialog.h"
#include "NetworkManager.h"
#include "ClientEvents.h"

class LoginDialog : public QWidget {
    Q_OBJECT
public:
    LoginDialog(QObject *parent = 0);

     //bool            event(QEvent *event);
    ~LoginDialog();

private:
    Ui::Form l_ui;
    QObject *parent;

private slots:
    void on_connectButton_clicked();
};

#endif // LOGINDIALOG_H
