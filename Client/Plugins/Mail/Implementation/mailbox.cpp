#include "mailbox.h"
#include "ui_mailbox.h"
#include "email.h"

mailbox::mailbox(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::mailboxClass)
{
    from = "inconnu";
    to = "";
    subject = "aucun sujet";
    content = "";
    qDebug("lancement interface mail");
    ui->setupUi(this);
    hideall();
    QObject::connect( ui->new_message, SIGNAL(clicked()), this, SLOT(new_message()) );
    QObject::connect( ui->mailbox, SIGNAL(clicked()), this, SLOT(show_box()) );
    QObject::connect( ui->pushButton_send, SIGNAL(clicked()), this, SLOT(send_message()) );
}

mailbox::~mailbox()
{
    delete ui;
}

void mailbox::new_message()
{
    hideall();
    ui->widget_send_message->show();
}

void mailbox::show_box()
{
    hideall();
    ui->widget_mailbox->show();
    qDebug("nouveau message");


}

void mailbox::send_message()
{
    this->from = ui->lineEdit_from->text();
    this->to = ui->lineEdit_to->text();
    this->subject = ui->lineEdit_subject->text();
    this->content = ui->content_message->toPlainText();
    qDebug() <<"from : " << this->from;
    qDebug() <<"to : " << this->to;
   qDebug() <<"Subject : " << this->subject;
   qDebug() <<"conent : " << this->content;

    email *send_mail = new email();
}

void mailbox::hideall()
{
    ui->widget_send_message->hide();
    ui->widget_mailbox->hide();
}
