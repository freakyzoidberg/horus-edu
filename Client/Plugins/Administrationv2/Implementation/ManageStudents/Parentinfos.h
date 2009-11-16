#ifndef PARENTINFOS_H
#define PARENTINFOS_H

#include <QFrame>
#include <QComboBox>
#include "../../../../../Common/UserData.h"
class ParentInfos : public QFrame
{
public:
    ParentInfos();
    ParentInfos(UserData *d);
    QComboBox*   getParent() { return parent; }
private:
    QComboBox *parent;

};

#endif // PARENTINFOS_H
