#ifndef ITEMS_H
#define ITEMS_H
#include <QWidget>
#include <QPushButton>
#include <QDockWidget>
#include <QSizeGrip>

#include "WhiteBoard.h"

class Items : public QSizeGrip
{
    Q_OBJECT
public:
    Items();
    Items(WhiteBoard *);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

public slots:
    void   moveToDock();
    void   restore();

protected:
    void    mousePressEvent(QMouseEvent *event);

private:
    WhiteBoard      *board;
    QPushButton     *small;
    QPushButton     *openItem, *closeItem;
};

#endif // ITEMS_H
