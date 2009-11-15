#ifndef ITEMS_H
#define ITEMS_H

#include <QWidget>
#include <QPushButton>
#include <QDockWidget>
#include <QSizeGrip>
#include <QMouseEvent>
#include <QGridLayout>

#include "WhiteBoard.h"

class Items : public QWidget
{
    Q_OBJECT
public:
    Items(QWidget *parent, WhiteBoard *, ILesson* lesson, int id, QString, QString);
    ~Items();

    bool            getIsDocked();
    void            setMainWidget(QWidget *);
    QWidget         *getMainWidget();
    inline ILesson* getLesson() const { return lesson; }

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
    QGridLayout     *_layout;
    ILesson*        lesson;
};

#endif // ITEMS_H
