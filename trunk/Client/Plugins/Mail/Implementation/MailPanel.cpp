#include "MailPanel.h"
#include <QPushButton>
#include <QComboBox>
#include <QTableView>

MailPanel::MailPanel(): QWidget()
{
    QPushButton *writemail = new QPushButton(tr("Write Mail"));
    QComboBox *mailaccnt = new QComboBox();
    QVBoxLayout *menuleft = new QVBoxLayout();
    QVBoxLayout *contentright = new QVBoxLayout();

    QLabel *toto = new QLabel();
    QTableView *MailList = new QTableView();
    toto->setText("test");
    menuleft->addWidget(mailaccnt,0, Qt::AlignTop);
    menuleft->addWidget(writemail,1, Qt::AlignTop);
    contentright->addWidget(MailList);
    layout.addLayout(menuleft->layout(),1);
    layout.addLayout(contentright->layout(),4);
    setLayout(layout.layout());
}

MailPanel::~MailPanel()
{
}
