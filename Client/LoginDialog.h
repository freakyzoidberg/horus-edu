#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QtGui/QWidget>
#include "ui_LoginDialog.h"
#include "NetworkManager.h"

class LoginDialog : public QWidget {
    Q_OBJECT
public:
    LoginDialog(QObject *parent = 0);
    ~LoginDialog();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::Form l_ui;

private slots:
    void on_connectButton_clicked();
};

#endif // LOGINDIALOG_H
