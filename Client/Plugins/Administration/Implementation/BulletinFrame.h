#ifndef BULLETINFRAME_H
#define BULLETINFRAME_H

#include <QWidget>
#include "../../../../Common/TreeData.h"
#include "../../../../Common/UserData.h"
#include "../../../../Common/EventData.h"

class BulletinFrame : public QWidget
{
public:
    BulletinFrame(TreeDataPlugin *tree, UserDataPlugin *user, EventDataPlugin *event);
};

#endif // BULLETINFRAME_H
