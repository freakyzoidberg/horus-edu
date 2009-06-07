#ifndef IDISPLAYABLE_H
#define IDISPLAYABLE_H

#include <QWidget>

class   IDisplayable
{
 public:
    virtual void setCentralWidget(QWidget *widget) = 0;
};

#endif // IDISPLAYABLE_H