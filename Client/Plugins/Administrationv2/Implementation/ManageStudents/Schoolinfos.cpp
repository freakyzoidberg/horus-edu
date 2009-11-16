#include "Schoolinfos.h"

SchoolInfos::SchoolInfos()
{
    QGridLayout *BasicLayout = new QGridLayout(this);

    raisons_renoublement = new QLineEdit();
    nb_redoublement = new QSpinBox();
    moyenne =new QLineEdit();
    comment = new QTextEdit();


    BasicLayout->addWidget(new QLabel(tr("redoublement")), 0, 0);
    BasicLayout->addWidget(nb_redoublement, 0, 1);
    BasicLayout->addWidget(new QLabel(tr("raisons")), 1, 0);
    BasicLayout->addWidget(raisons_renoublement, 1, 1);

    BasicLayout->addWidget(new QLabel(tr("moyenne")), 2, 0);
    BasicLayout->addWidget(moyenne, 2, 1);

    BasicLayout->addWidget(new QLabel(tr("Comments")), 3, 0);
    BasicLayout->addWidget(comment, 3, 1);

    this->setLayout(BasicLayout);
}



SchoolInfos::SchoolInfos(UserData *d)
{
    QGridLayout *BasicLayout = new QGridLayout(this);

    raisons_renoublement = new QLineEdit();
    raisons_renoublement->setText("pas dans les data");
    nb_redoublement = new QSpinBox();
    //nb_redoublement->setValue();
    moyenne =new QLineEdit();
    //moyenne->setText(d->);
    comment = new QTextEdit();


    BasicLayout->addWidget(new QLabel(tr("redoublement")), 0, 0);
    BasicLayout->addWidget(nb_redoublement, 0, 1);
    BasicLayout->addWidget(new QLabel(tr("raisons")), 1, 0);
    BasicLayout->addWidget(raisons_renoublement, 1, 1);

    BasicLayout->addWidget(new QLabel(tr("moyenne")), 2, 0);
    BasicLayout->addWidget(moyenne, 2, 1);

    BasicLayout->addWidget(new QLabel(tr("Comments")), 3, 0);
    BasicLayout->addWidget(comment, 3, 1);

    this->setLayout(BasicLayout);
}
