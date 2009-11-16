#include "Socialinfos.h"

SocialInfos::SocialInfos()
{
    QGridLayout *BasicLayout = new QGridLayout(this);

    referent = new QLineEdit();
    motif = new QTextEdit();
    aides = new QLineEdit();

    BasicLayout->addWidget(new QLabel(tr("Referent")), 0, 0);
    BasicLayout->addWidget(referent, 0, 1);

    BasicLayout->addWidget(new QLabel(tr("Motif d inscription")), 1, 0);
    BasicLayout->addWidget(motif, 1, 1);

    BasicLayout->addWidget(new QLabel(tr("Aides financiaires")), 2, 0);
    BasicLayout->addWidget(aides, 2, 1);

    this->setLayout(BasicLayout);
}

SocialInfos::SocialInfos(UserData *d)
{
    QGridLayout *BasicLayout = new QGridLayout(this);

    referent = new QLineEdit();
    motif = new QTextEdit();
    aides = new QLineEdit();

    BasicLayout->addWidget(new QLabel(tr("referent")), 0, 0);
    BasicLayout->addWidget(referent, 0, 1);

    BasicLayout->addWidget(new QLabel(tr("motif d inscription")), 1, 0);
    BasicLayout->addWidget(motif, 1, 1);

    BasicLayout->addWidget(new QLabel(tr("Aides financiaires")), 2, 0);
    BasicLayout->addWidget(aides, 2, 1);

    this->setLayout(BasicLayout);
}
