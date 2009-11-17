#include "Parentinfos.h"
#include <QGridLayout>
#include <QLabel>
ParentInfos::ParentInfos()
{
    setProperty("isFormFrame", true);
    QGridLayout *BasicLayout = new QGridLayout(this);

    BasicLayout->setMargin(8);
    BasicLayout->setSpacing(4);

    parent = new QComboBox(this);

    QLabel *label = new QLabel(tr("Parent"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 0, 0);
    BasicLayout->addWidget(parent, 0, 1);
	BasicLayout->setColumnStretch(1, 1);



BasicLayout->setColumnMinimumWidth(0,150);
    this->setLayout(BasicLayout);
}


ParentInfos::ParentInfos(UserData *)
{
    setProperty("isFormFrame", true);
    QGridLayout *BasicLayout = new QGridLayout(this);

    BasicLayout->setMargin(8);
    BasicLayout->setSpacing(4);

	parent = new QComboBox(this);

    QLabel *label = new QLabel(tr("Parent"));
    label->setProperty("isFormLabel", true);
    BasicLayout->addWidget(label, 0, 0);
    BasicLayout->addWidget(parent, 0, 1);
	BasicLayout->setColumnStretch(1, 1);


    BasicLayout->setColumnMinimumWidth(0,150);
    this->setLayout(BasicLayout);
}


