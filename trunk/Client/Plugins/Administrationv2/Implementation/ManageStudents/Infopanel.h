#ifndef INFOPANEL_H
#define INFOPANEL_H

#include <QWidget>
#include "../../../../../Common/UserData.h"
#include <QGridLayout>
#include <QLabel>
class InfoPanel : public QWidget
{
	Q_OBJECT

public:
    InfoPanel(UserData *it);
};

#endif // INFOPANEL_H
