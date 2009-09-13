#include "WhiteBoard.h"
#include "Items.h"
#include <QDebug>
WhiteBoard::WhiteBoard()
{
    setAcceptDrops(true);
    setAutoFillBackground(false);


}

void   WhiteBoard::setTmp(Items *item)
{
    tmp = item;
}


Items  *WhiteBoard::getTmp()
{
    return tmp;
}

void WhiteBoard::dragEnterEvent(QDragEnterEvent *event)
 {
             event->acceptProposedAction();

 }

 void WhiteBoard::dragMoveEvent(QDragMoveEvent *event)
 {

             event->accept();

 }

 void WhiteBoard::dropEvent(QDropEvent *event)
 {
//         const QMimeData *mime = event->mimeData();
  //       QByteArray itemData = mime->data("application/x-fridgemagnet");
    //QDataStream dataStream(&itemData, QIODevice::ReadOnly);

     qDebug() << event->mimeData()->property("hotspot");
         QString text;
         QPoint offset(event->mimeData()->property("hotspot").toPoint());

         //dataStream >> text >> offset;
        //dataStream >> offset;

         //Items *newLabel = new Items(this);
         //newLabel->move(event->pos() - offset);
         //newLabel->show();

           tmp->move(event->pos() - offset);
            tmp->raise();
           tmp->show();
           tmp->setVisible(true);
           tmp->parentWidget()->repaint();
qDebug() << "finalement : " << event->mimeData()->isWidgetType() << " " << event->mimeData();
qDebug() << "Et sa position : " << event->pos().x() << " et " << event->pos().y();
qDebug() << "Et sa taille : " << tmp->size().width() << " et " << tmp->size().height();
             event->acceptProposedAction();


 }
