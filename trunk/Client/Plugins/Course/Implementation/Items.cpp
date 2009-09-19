#include "Items.h"
#include <QPalette>
#include <QDrag>
#include <QPixmap>
#include <QApplication>
#include <QDesktopWidget>
#include <QPushButton>
#include <QIcon>
#include <QVector>

#include <QDebug>

Items::Items(WhiteBoard *papyrus, int id) : QSizeGrip(papyrus), id(id)
{
    this->setAcceptDrops(true);
    this->board = papyrus;

    closeItem = new QPushButton(this);
    closeItem->setIcon(QIcon(":/close.png"));
    closeItem->setGeometry(0, 0, 20, 20);

    openItem = new QPushButton(this);
    openItem->setIcon(QIcon(":/fleche_haut_vert.png"));
    openItem->setGeometry(21, 0, 20, 20);

    this->setStyleSheet("Items{border: 1px dotted #888888;}");
    this->connect(closeItem, SIGNAL(clicked()), this, SLOT(close()));
    this->connect(openItem, SIGNAL(clicked()), this, SLOT(moveToDock()));
    this->setMinimumHeight(25);
    this->setMinimumWidth(45);

    this->isDocked = false;
    this->isMoving = false;
    this->isResizing = false;

    this->setWindowFlags(Qt::SubWindow);
}

bool    Items::getIsDocked()
{
    return this->isDocked;
}

void    Items::leaveEvent(QEvent *event)
{
	this->closeItem->hide();
	this->openItem->hide();
}

void    Items::enterEvent(QEvent *event)
{
	this->closeItem->show();
	this->openItem->show();
}

void    Items::mouseReleaseEvent(QMouseEvent *event)
{
    if (!this->isResizing)
        return ;

    X = event->pos().y();
    Y = event->pos().x();

    this->hide();

    setGeometry(this->pos().x(), this->pos().y(),
                this->size().height() + (Y - saveY),
                this->size().width() + (X - saveX));
    repaint();
    this->isResizing = false;
    this->show();
}

void Items::mouseMoveEvent(QMouseEvent *event)
{
	qDebug() << event->pos() << this->width() << this->height();
}

void Items::mousePressEvent(QMouseEvent *event)
{
    if ((event->pos().x() >= this->size().width() - 15)
        && (event->pos().x() <= this->size().width() + 15)
        && (event->pos().y() >= this->size().height() - 15)
        && (event->pos().y() <= this->size().height() + 15))
        {
            saveX = event->pos().x();
            saveY = event->pos().y();
            this->isResizing = true;
            return ;
        }

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
         show();     //show();
 }

void    Items::restore()
{
    int pos = 0;
    show();
    small->hide();
    for (int i = 0; i < board->button.count(); ++i)
    {
        if (board->button[i] != small)
        {
            board->button[i]->hide();
            board->button[i]->show();
            board->button[i]->setGeometry(pos, 5, 20, 20);
            board->button[i]->repaint();
            pos += 21;
        }
        else
        {
            board->button.remove(i);
            delete small;
        }
    }
    this->board->setPosInDoc(pos);
}

void    Items::moveToDock()
{
    this->hide();
    small = new QPushButton(this->board->dock);
    small->setIcon(QIcon(":/fleche_bas_vert.png"));
    small->setGeometry(board->getPosInDoc(), 5, 20, 20);
    this->board->setPosInDoc(board->getPosInDoc() + 21);
    board->button.append(small);
    small->show();
    connect(small, SIGNAL(clicked()), this, SLOT(restore()));
}

int		Items::getId()
{
	return id;
}

