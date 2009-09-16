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
};

#endif // ITEMS_H
