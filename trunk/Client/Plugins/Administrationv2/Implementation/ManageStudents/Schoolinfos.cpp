#include "Schoolinfos.h"

SchoolInfos::SchoolInfos()
{
    QGridLayout *BasicLayout = new QGridLayout(this);

    raisons_redoublement = new QLineEdit();
    nb_redoublement = new QSpinBox();
    //moyenne =new QLineEdit();
    //comment = new QTextEdit();


    BasicLayout->addWidget(new QLabel(tr("Redoublement")), 0, 0);
    BasicLayout->addWidget(nb_redoublement, 0, 1);
    BasicLayout->addWidget(new QLabel(tr("Raisons")), 1, 0);
    BasicLayout->addWidget(raisons_redoublement, 1, 1);

    //BasicLayout->addWidget(new QLabel(tr("Moyenne")), 2, 0);
    //BasicLayout->addWidget(moyenne, 2, 1);

    //BasicLayout->addWidget(new QLabel(tr("Comments")), 3, 0);
    //BasicLayout->addWidget(comment, 3, 1);
BasicLayout->setColumnMinimumWidth(0,150);
    this->setLayout(BasicLayout);
}



SchoolInfos::SchoolInfos(UserData *d)
{
    QGridLayout *BasicLayout = new QGridLayout(this);

    raisons_redoublement = new QLineEdit();
   // raisons_redoublement->setText(d->comment().split("|:/:|:/|").at(2));
    nb_redoublement = new QSpinBox();
    //nb_redoublement->setValue();
    nb_redoublement->setValue(d->repeatedYears());
  //  moyenne =new QLineEdit();
    //moyenne->setText(d->);
    //comment = new QTextEdit();
    //comment->setText(d->comment());





    BasicLayout->addWidget(new QLabel(tr("redoublement")), 0, 0);
    BasicLayout->addWidget(nb_redoublement, 0, 1);
    BasicLayout->addWidget(new QLabel(tr("raisons")), 1, 0);
    BasicLayout->addWidget(raisons_redoublement, 1, 1);

 //   BasicLayout->addWidget(new QLabel(tr("moyenne")), 2, 0);
   // BasicLayout->addWidget(moyenne, 2, 1);

   // BasicLayout->addWidget(new QLabel(tr("Comments")), 3, 0);
   // BasicLayout->addWidget(comment, 3, 1);
BasicLayout->setColumnMinimumWidth(0,150);
    this->setLayout(BasicLayout);
}
