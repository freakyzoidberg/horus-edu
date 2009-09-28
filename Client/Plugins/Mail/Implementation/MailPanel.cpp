#include "MailPanel.h"
#include <QPushButton>
#include <QComboBox>
#include <QTableView>
#include <QLayoutItem>

MailPanel::MailPanel(): QWidget()
{
    QPushButton *writemail = new QPushButton(tr("Write Mail"));
    QPushButton *mailbox = new QPushButton(tr("MailBox"));
    QComboBox *mailaccnt = new QComboBox();
    QVBoxLayout *menuleft = new QVBoxLayout();

    menuleft->setSizeConstraint(QLayout::SetMaximumSize);
    contentright = new QVBoxLayout();

    this->Mlist = new MailList();
    this->Mform = new MailForm();
    menuleft->addWidget(mailaccnt,0, Qt::AlignTop);
    menuleft->addWidget(mailbox,0, Qt::AlignTop);
    menuleft->addWidget(writemail,1, Qt::AlignTop);
    contentright->addWidget(this->Mlist);
    contentright->setMargin(0);


    layout.addLayout(menuleft->layout(),0);
    layout.addLayout(contentright->layout(),4);





    setLayout(layout.layout());


    connect(writemail, SIGNAL(clicked()), this, SLOT(changetowrite()));
    connect(mailbox, SIGNAL(clicked()), this, SLOT(changetolist()));
}

MailPanel::~MailPanel()
{
}

void MailPanel::changetowrite()
{
    QLayoutItem *child;
    while ((child = contentright->takeAt(0)) != 0) {
     child->widget()->close();
 }

contentright->addWidget(this->Mform);
this->Mform->show();
}

void MailPanel::changetolist()
{
    QLayoutItem *child;
    while ((child = contentright->takeAt(0)) != 0) {
     child->widget()->close();
 }
    contentright->addWidget(this->Mlist);
    this->Mlist->show();

}


