#ifndef IITEMS_H
#define IITEMS_H

#include <QSizeGrip>
#include <QGridLayout>

class   IItems : public QSizeGrip
{
public:
    IItems(QWidget *papyrus) : QSizeGrip(papyrus) {}
    virtual void            setMainWidget(QWidget *) = 0;
    virtual QWidget         *getMainWidget() = 0;
};

#endif // IITEMS_H
