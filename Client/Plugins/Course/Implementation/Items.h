#ifndef ITEMS_H
#define ITEMS_H
#include <QWidget>
#include <QPushButton>

#include "WhiteBoard.h"
class Items : public QWidget
{
public:
    Items();
    Items(WhiteBoard *);
         QPushButton *openItem, *closeItem;

    public slots:
     void closing();

    protected:
     void mousePressEvent(QMouseEvent *event);


   private:
        WhiteBoard  *board;


};

#endif // ITEMS_H
