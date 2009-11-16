#include "Socialinfos.h"

SocialInfos::SocialInfos()
{
    setProperty("isFormFrame", true);
    QGridLayout *BasicLayout = new QGridLayout(this);

    referent = new QLineEdit();
    motif = new QTextEdit();
    aides = new QLineEdit();

    BasicLayout->setMargin(8);
    BasicLayout->setSpacing(4);

    QLabel* label = new QLabel(tr("Referent"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 0, 0);
    BasicLayout->addWidget(referent, 0, 1);

    label = new QLabel(tr("Motif d inscription"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 1, 0);
    BasicLayout->addWidget(motif, 1, 1);

    label = new QLabel(tr("Aides financiaires"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 2, 0);
    BasicLayout->addWidget(aides, 2, 1);
    BasicLayout->setColumnMinimumWidth(0,150);
    this->setLayout(BasicLayout);
}

SocialInfos::SocialInfos(UserData *d)
{
    QGridLayout *BasicLayout = new QGridLayout(this);

    referent = new QLineEdit();
    motif = new QTextEdit();
    motif->setPlainText(d->subscriptionReason());
    aides = new QLineEdit();





    QStringList tmp = d->comment().split("|:/:|:/|");
    if (tmp.count() >= 3)
    {
    referent->setText(tmp.at(0));
    aides->setText(tmp.at(1));
    }
    BasicLayout->addWidget(new QLabel(tr("referent")), 0, 0);
    BasicLayout->addWidget(referent, 0, 1);

    BasicLayout->addWidget(new QLabel(tr("motif d inscription")), 1, 0);
    BasicLayout->addWidget(motif, 1, 1);

    BasicLayout->addWidget(new QLabel(tr("Aides financiaires")), 2, 0);
    BasicLayout->addWidget(aides, 2, 1);
BasicLayout->setColumnMinimumWidth(0,150);
    this->setLayout(BasicLayout);
}
