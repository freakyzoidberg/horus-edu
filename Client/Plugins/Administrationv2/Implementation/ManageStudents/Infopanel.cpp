#include "Infopanel.h"

InfoPanel::InfoPanel(UserData *it)
{
QGridLayout *layout = new QGridLayout();

if (it != 0)
{


layout->addWidget(new QLabel(tr("name :")), 0,0);
layout->addWidget(new QLabel(tr("birthday :")),1,0);
layout->addWidget(new QLabel(tr("address :")),2,0);











QLabel *na = new QLabel(it->surname()+ " " + it->name());
na->setWordWrap(true);
    layout->addWidget(na, 0,1);

    QLabel *bd = new QLabel(it->birthDate().toString());
    bd->setWordWrap(true);
    layout->addWidget(bd, 1,1);
    QLabel *add = new QLabel(it->address());
    add->setWordWrap(true);
    layout->addWidget(add, 2,1);
    }
setLayout(layout);
}
