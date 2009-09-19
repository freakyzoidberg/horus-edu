#ifndef ITEMS_H
#define ITEMS_H

#include <QWidget>
#include <QPushButton>
#include <QDockWidget>
#include <QSizeGrip>
#include <QMouseEvent>

#include "WhiteBoard.h"
class Items : public QSizeGrip
{
    Q_OBJECT
public:
    Items();
    Items(WhiteBoard *, int id);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    bool getIsDocked();


public slots:
    void   moveToDock();
    void   restore();
    int    getId();

protected:
    void    mousePressEvent(QMouseEvent *event);
    void    mouseMoveEvent(QMouseEvent *event);
    void    mouseReleaseEvent(QMouseEvent *event);


private:
    WhiteBoard      *board;
    QPushButton     *small;
    int             id;
    QPushButton     *openItem, *closeItem;
    bool            isDocked;
    bool            isMoving;
    bool            isResizing;
    int             X, Y, saveX, saveY;
};

#endif // ITEMS_H
