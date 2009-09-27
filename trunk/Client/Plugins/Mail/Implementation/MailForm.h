#ifndef MAILFORM_H
#define MAILFORM_H

#include <QtGui/QWidget>
#include <QListWidget>
#include <QStackedWidget>
#include <QtGui>
#include <QHBoxLayout>
#include <QVBoxLayout>
//class MailForm;
class MailForm : public QWidget
{

public:
    MailForm();
    ~MailForm();
private :
    QLineEdit *to_value;
    QLineEdit *cc_value;
    QLineEdit *bcc_value;
    QLineEdit *subject_value;
    QTextEdit *content_value;
};

#endif // MAILPANEL_H
