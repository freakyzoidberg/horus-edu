#include "items.h"
#include <QPalette>
#include <QDrag>
#include <QPixmap>
#include <QApplication>
#include <QDesktopWidget>

#include <QDebug>
Items::Items()
{
    this->setAutoFillBackground(true);
    QPalette p(this->palette());
    p.setColor(QPalette::Background, Qt::blue);
    this->setPalette(p);
    this->setAcceptDrops(true);
}

Items::Items(WhiteBoard *papyrus) : QWidget(papyrus)
{
    this->setAutoFillBackground(true);
    QPalette p(this->palette());
    p.setColor(QPalette::Background, Qt::blue);
    this->setPalette(p);
    this->setAcceptDrops(true);
    this->move(100,100);
    this->board = papyrus;
}

void Items::mousePressEvent(QMouseEvent *event)
 {
    QByteArray itemData;
     QDataStream dataStream(&itemData, QIODevice::WriteOnly);
     dataStream << QPoint(event->pos() - rect().topLeft());

    this->board->setTmp(this);

    qDebug() << "addr : "<< this->parentWidget();
     QDrag *drag = new QDrag(this);
 //    drag->setMimeData(mimeData);
     QMimeData *mimeData = new QMimeData;
     mimeData->setData("*/*", itemData);

        int x,y,w,h;

        w = this->width();
        h = this->height();
        x=this->x();
        y=this->y();

        //QPixmap mini = QPixmap::grabWindow( QApplication::desktop()->winId(),  x,y, w, h );

    QPixmap mini = QPixmap::grabWidget(this);


     drag->setMimeData(mimeData);

     drag->setHotSpot(event->pos() - rect().topLeft());
     drag->setPixmap(mini);


     hide();

     if (drag->exec(Qt::MoveAction | Qt::CopyAction, Qt::CopyAction) == Qt::MoveAction)
     {
         close();
     }
     else
         show();

 }
