#include "Schoolinfos.h"

SchoolInfos::SchoolInfos()
{
    setProperty("isFormFrame", true);
    QGridLayout *BasicLayout = new QGridLayout(this);

    //raisons_redoublement = new QLineEdit();
    nb_redoublement = new QSpinBox();
    //moyenne =new QLineEdit();
    //comment = new QTextEdit();

    BasicLayout->setMargin(8);
    BasicLayout->setSpacing(4);

    QLabel* label = new QLabel(tr("Redoublement"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 0, 0);
    BasicLayout->addWidget(nb_redoublement, 0, 1);

    /* Supprime dans Ecoline v1.0.1
    label = new QLabel(tr("Raisons"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 1, 0);
    BasicLayout->addWidget(raisons_redoublement, 1, 1);
    */

    //BasicLayout->addWidget(new QLabel(tr("Moyenne")), 2, 0);
    //BasicLayout->addWidget(moyenne, 2, 1);

    //BasicLayout->addWidget(new QLabel(tr("Comments")), 3, 0);
    //BasicLayout->addWidget(comment, 3, 1);
BasicLayout->setColumnMinimumWidth(0,150);
    this->setLayout(BasicLayout);
}



SchoolInfos::SchoolInfos(UserData *d)
{
    setProperty("isFormFrame", true);
    QGridLayout *BasicLayout = new QGridLayout(this);
    BasicLayout->setMargin(8);
    BasicLayout->setSpacing(4);

    //raisons_redoublement = new QLineEdit();
    //QStringList tmp = d->comment().split("|:/:|:/|");
    //if (tmp.count() >= 2)
    //raisons_redoublement->setText(d->comment().split("|:/:|:/|").at(2));
    nb_redoublement = new QSpinBox();
    //nb_redoublement->setValue();
    nb_redoublement->setValue(d->repeatedYears());
  //  moyenne =new QLineEdit();
    //moyenne->setText(d->);
    //comment = new QTextEdit();
    //comment->setText(d->comment());





    QLabel* label = new QLabel(tr("Redoublement"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 0, 0);
    BasicLayout->addWidget(nb_redoublement, 0, 1);

    /* Supprime dans ecoline v1.0.1s
    label = new QLabel(tr("Raisons"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 1, 0);
    BasicLayout->addWidget(raisons_redoublement, 1, 1);
    */
 //   BasicLayout->addWidget(new QLabel(tr("moyenne")), 2, 0);
   // BasicLayout->addWidget(moyenne, 2, 1);

   // BasicLayout->addWidget(new QLabel(tr("Comments")), 3, 0);
   // BasicLayout->addWidget(comment, 3, 1);
BasicLayout->setColumnMinimumWidth(0,150);
    this->setLayout(BasicLayout);
}
