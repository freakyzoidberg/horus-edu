#include "MailForm.h"

MailForm::MailForm()
{
    QVBoxLayout *total = new QVBoxLayout();
    QHBoxLayout *ligne1 = new QHBoxLayout();
    QHBoxLayout *ligne1_1 = new QHBoxLayout();
    QHBoxLayout *ligne1_2 = new QHBoxLayout();
    QHBoxLayout *ligne2 = new QHBoxLayout();
    QHBoxLayout *ligne3 = new QHBoxLayout();
    QHBoxLayout *ligne4 = new QHBoxLayout();


    QLabel *to = new QLabel(tr("To :"));
    to_value = new QLineEdit();
    to_value->setMinimumSize(500,1);
    ligne1->addWidget(to,0,Qt::AlignLeft);
    ligne1->addWidget(to_value,1);


    QLabel *cc = new QLabel(tr("cc :"));
    cc_value = new QLineEdit();
    cc_value->setMinimumSize(500,1);
    ligne1_1->addWidget(cc,0,Qt::AlignLeft);
    ligne1_1->addWidget(cc_value,1);


    QLabel *bcc = new QLabel(tr("bcc :"));
    bcc_value = new QLineEdit();
    bcc_value->setMinimumSize(500,1);
    ligne1_2->addWidget(bcc,0,Qt::AlignLeft);
    ligne1_2->addWidget(bcc_value,1);

    QLabel *subject = new QLabel(tr("Subject :"));
    subject_value = new QLineEdit();
    subject_value->setMinimumSize(500,10);
    ligne2->addWidget(subject,0,Qt::AlignLeft);
    ligne2->addWidget(subject_value,1);


    content_value = new QTextEdit();
    ligne3->addWidget(content_value,1);


    QPushButton *send = new QPushButton(tr("Send"));
    ligne4->addWidget(send,1, Qt::AlignRight);

    total->addLayout(ligne1->layout(),0);
    total->addLayout(ligne1_1->layout(),0);
    total->addLayout(ligne1_2->layout(),0);
    total->addLayout(ligne2->layout(),0);
    total->addLayout(ligne3->layout(),1);
    total->addLayout(ligne4->layout(),0);

    total->setAlignment(ligne1->layout(), Qt::AlignTop);
    total->setAlignment(ligne1_1->layout(), Qt::AlignTop);
    total->setAlignment(ligne1_2->layout(), Qt::AlignTop);
    total->setAlignment(ligne2->layout(), Qt::AlignTop);
    total->setAlignment(ligne3->layout(), Qt::AlignTop);
    total->setAlignment(ligne4->layout(), Qt::AlignTop);




    this->setLayout(total->layout());
}

MailForm::~MailForm()
{
}
