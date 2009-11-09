#ifndef USERINFORMATIONS_H
#define USERINFORMATIONS_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>

#include "../../../../Common/UserData.h"

class UserInformations : public QWidget
{
public:
    UserInformations();
    void    setInformations(UserData *);

private:
    QGridLayout *mainLayout;
    QLabel      *_name, *_firstname, *_picture, *_title, *_phone;
};

#endif // USERINFORMATIONS_H
