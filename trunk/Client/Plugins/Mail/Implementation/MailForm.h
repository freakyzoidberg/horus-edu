#ifndef MAILFORM_H
#define MAILFORM_H

#include <QtGui/QWidget>
#include <QListWidget>
#include <QStackedWidget>
#include <QtGui>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include                        "../../../../Common/DataImplementations/MailData/MailDataPlugin.h"
//class MailForm;
class MailForm : public QWidget
{
Q_OBJECT
public:
    MailForm(MailDataPlugin *MailPlugin);
    ~MailForm();

private :
    QLineEdit *to_value;
    QLineEdit *cc_value;
    QLineEdit *bcc_value;
    QLineEdit *subject_value;
    QTextEdit *content_value;
    QPushButton *sendbtn;
    MailDataPlugin *_MailPlugin;

private slots:
        void mysendmail();
        void validate();

};

#endif // MAILPANEL_H