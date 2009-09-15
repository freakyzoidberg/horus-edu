#ifndef ITEMS_H
#define ITEMS_H
#include <QWidget>
#include <QPushButton>
#include <QDockWidget>

#include "WhiteBoard.h"
class Items : public QWidget
{
    Q_OBJECT
public:
    Items();
    Items(WhiteBoard *);
         QPushButton *openItem, *closeItem;

    public slots:
     void moveToDock();
     void   restore();

    protected:
     void mousePressEvent(QMouseEvent *event);


   private:
        WhiteBoard  *board;


};

#endif // ITEMS_H
