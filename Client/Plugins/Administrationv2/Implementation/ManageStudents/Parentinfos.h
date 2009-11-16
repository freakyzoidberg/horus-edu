#ifndef PARENTINFOS_H
#define PARENTINFOS_H

#include <QWidget>
#include <QComboBox>
#include "../../../../../Common/UserData.h"
class ParentInfos : public QWidget
{
public:
    ParentInfos();
    ParentInfos(UserData *d);
    QComboBox*   getParent() { return parent; }
private:
    QComboBox *parent;

};

#endif // PARENTINFOS_H
