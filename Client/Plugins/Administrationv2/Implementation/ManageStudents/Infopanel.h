#ifndef INFOPANEL_H
#define INFOPANEL_H

#include <QWidget>
#include "../../../../../Common/UserData.h"
#include <QGridLayout>
#include <QLabel>
class InfoPanel : public QWidget
{
public:
    InfoPanel(UserData *it);
};

#endif // INFOPANEL_H
