#include "AdminFram.h"

AdminFram::AdminFram(QWidget *parent) : QWidget(parent)
{
    setupUi(this);
    tF = new TreeFram(this);
    uF = new UserFram(this);
    this->mainLayout->addWidget(tF, 0,0);
    this->mainLayout->addWidget(uF, 0,1);
}

void AdminFram::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}

void AdminFram::packetManager(QVariantHash response)
{
    if (response["Request"] == "changePassword" ||
        response["Request"] == "listUsers" ||
        response["Request"] == "setUserInfo" ||
        response["Request"] == "createNewUser" ||
        response["Request"] == "disableUser")
    {

    }
    else
    {

    }
}
