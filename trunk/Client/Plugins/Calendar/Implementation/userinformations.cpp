#include <QPixmap>

#include "userinformations.h"

UserInformations::UserInformations()
{
    mainLayout = new QGridLayout(this);
    this->_title = new QLabel(tr("User's Calendar:"));
    this->_firstname = new QLabel();
    this->_name = new QLabel();
    this->_picture = new QLabel();
    this->_phone = new QLabel();

    mainLayout->addWidget(_title, 0, 0, 1, 2);
    mainLayout->addWidget(_picture, 1, 0, 3, 1);
    mainLayout->addWidget(_firstname, 1, 1, 1, 1);
    mainLayout->addWidget(_name, 2, 1, 1, 1);
    mainLayout->addWidget(_phone, 3, 1, 1, 1);
}

void    UserInformations::setInformations(UserData *user)
{
    _firstname->setText(user->name());
    _name->setText(user->surname());
    _phone->setText(user->phone1());
    _picture->setPixmap(QPixmap(":/anonymous.png")); //user->picture() qd yen aura une
}
