#include "Items.h"
#include <QPalette>
#include <QDrag>
#include <QPixmap>
#include <QApplication>
#include <QDesktopWidget>
#include <QPushButton>
#include <QIcon>

#include <QDebug>

Items::Items(WhiteBoard *papyrus) : QSizeGrip(papyrus)
{
    this->setAcceptDrops(true);
    this->board = papyrus;

    closeItem = new QPushButton(this);
    closeItem->setIcon(QIcon(":/close.png"));
    //closeItem->setText("C");
    closeItem->setGeometry(0, 0, 20, 20);

    openItem = new QPushButton(this);
    openItem->setIcon(QIcon(":/fleche_haut_vert.png"));
    //openItem->setText("R");
    openItem->setGeometry(21, 0, 20, 20);

    this->connect(closeItem, SIGNAL(clicked()), this, SLOT(close()));
    this->connect(openItem, SIGNAL(clicked()), this, SLOT(moveToDock()));
}

void Items::leaveEvent(QEvent *event)
{
	this->closeItem->hide();
	this->openItem->hide();
}

void Items::enterEvent(QEvent *event)
{
	this->closeItem->show();
	this->openItem->show();
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
    delete small;
    this->board->setPosInDoc(board->getPosInDoc() - 21);
}

void    Items::moveToDock()
{
    this->hide();
    this->board->setPosInDoc(board->getPosInDoc() + 21);
    small = new QPushButton(this->board->dock);
    small->setIcon(QIcon(":/fleche_bas_vert.png"));
    small->setGeometry(this->board->getPosInDoc(), 25, 20, 20);
    small->show();
    connect(small, SIGNAL(clicked()), this, SLOT(restore()));
}

