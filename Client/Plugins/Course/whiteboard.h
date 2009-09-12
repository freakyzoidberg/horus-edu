#ifndef WHITEBOARD_H
#define WHITEBOARD_H

#include <QWidget>
#include <QDragEnterEvent>

class Items;

class WhiteBoard : public QWidget
{
public:
    WhiteBoard();
     void   setTmp(Items *);
     Items  *getTmp();

protected:
     void dragEnterEvent(QDragEnterEvent *event);
     void dragMoveEvent(QDragMoveEvent *event);
     void dropEvent(QDropEvent *event);


 private:
        Items   *tmp;

};

#endif // WHITEBOARD_H
