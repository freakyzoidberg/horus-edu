#ifndef ITEMS_H
#define ITEMS_H
#include <QWidget>
#include "WhiteBoard.h"
class Items : public QWidget
{
public:
    Items();
    Items(WhiteBoard *);

    protected:
     void mousePressEvent(QMouseEvent *event);

   private:
        WhiteBoard  *board;

};

#endif // ITEMS_H
