#ifndef ITEMS_H
#define ITEMS_H

#include <QWidget>
#include <QPushButton>
#include <QDockWidget>
#include <QSizeGrip>
#include <QMouseEvent>
#include <QGridLayout>

#include "IItems.h"
#include "WhiteBoard.h"

class Items : public IItems
{
    Q_OBJECT
public:
                    Items();
                    ~Items();
                    Items(WhiteBoard *, int id, QString, QString);
    void            enterEvent(QEvent *event);
    void            leaveEvent(QEvent *event);
    bool            getIsDocked();
    void            setMainWidget(QWidget *);
    QWidget         *getMainWidget();

public slots:
    void            moveToDock();
    void            restore();
    int             getId();
    bool            deleteWidgets();

protected:
    void            mousePressEvent(QMouseEvent *event);
    void            mouseMoveEvent(QMouseEvent *event);
    void            mouseReleaseEvent(QMouseEvent *event);

private:
    WhiteBoard      *board;
    QPushButton     *small;
    QWidget         *mainWidget;
    QPushButton     *openItem, *closeItem;
    int             id;
    QString         title;
    QString         type;
    bool            isDocked;
    bool            isMoving;
    bool            isResizing;
    int             X, Y, saveX, saveY;
    QGridLayout     *layout;
};

#endif // ITEMS_H
