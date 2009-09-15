#include "Items.h"
#include <QPalette>
#include <QDrag>
#include <QPixmap>
#include <QApplication>
#include <QDesktopWidget>
#include <QPushButton>

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

    closeItem = new QPushButton(this);
    closeItem->setText("C");
    closeItem->setGeometry(0, 0, 15, 15);

    openItem = new QPushButton(this);
    openItem->setText("R");
    openItem->setGeometry(0, 15, 15, 15);

    this->connect(closeItem, SIGNAL(clicked()), this, SLOT(close()));
    this->connect(openItem, SIGNAL(clicked()), this, SLOT(moveToDock()));
}

void Items::mousePressEvent(QMouseEvent *event)
 {
    QByteArray itemData;
     QDataStream dataStream(&itemData, QIODevice::WriteOnly);
     dataStream << QPoint(event->pos() - rect().topLeft());

    this->board->setTmp(this);

    //qDebug() << "addr : "<< this->parentWidget();
     QDrag *drag = new QDrag(this);
 //
     QMimeData *mimeData = new QMimeData;
     mimeData->setProperty("hotspot", event->pos() - rect().topLeft());

        int x,y,w,h;

        w = this->width();
        h = this->height();
        x=this->x();
        y=this->y();

        //QPixmap mini = QPixmap::grabWindow( QApplication::desktop()->winId(),  x,y, w, h );

    QPixmap mini = QPixmap::grabWidget(this);


     drag->setMimeData(mimeData);
qDebug() << "Et sa position : " << this->x() << " et " << this->y();
     drag->setHotSpot(event->pos() - rect().topLeft());
     drag->setPixmap(mini);

    closeItem->hide();
     hide();

     if (drag->exec(Qt::MoveAction | Qt::CopyAction, Qt::CopyAction) == Qt::MoveAction)
     {
         //close();
         hide();
     }
     else
         show();
     //show();
 }

void    Items::restore()
{
    show();
}

void    Items::moveToDock()
{
    qDebug() << "jvais te reduire";
    this->hide();

    QPushButton *test = new QPushButton(this->board->dock);
    test->setText("Re");
    test->setGeometry(20, 20, 15, 15);
    test->show();
    connect(test, SIGNAL(clicked()), this, SLOT(restore()));
}

