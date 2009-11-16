#include "Parentinfos.h"
#include <QGridLayout>
#include <QLabel>
ParentInfos::ParentInfos()
{
    QGridLayout *BasicLayout = new QGridLayout(this);

    parent = new QComboBox();


    BasicLayout->addWidget(new QLabel(tr("Parent")), 0, 0);
    BasicLayout->addWidget(parent, 0, 1);



BasicLayout->setColumnMinimumWidth(0,150);
    this->setLayout(BasicLayout);
}


ParentInfos::ParentInfos(UserData *d)
{
    QGridLayout *BasicLayout = new QGridLayout(this);

    parent = new QComboBox();
    //parent->setMaximumHeight(50);

    BasicLayout->addWidget(new QLabel(tr("Parent")), 0, 0);
    BasicLayout->addWidget(parent, 0, 1);



    BasicLayout->setColumnMinimumWidth(0,150);
    this->setLayout(BasicLayout);
}


