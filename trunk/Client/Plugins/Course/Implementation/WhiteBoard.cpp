#include "WhiteBoard.h"
#include "Items.h"
#include <QDebug>
WhiteBoard::WhiteBoard()
{
    setAcceptDrops(true);

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
     if (event->mimeData()->hasFormat("*/*")) {
         if (children().contains(event->source())) {
             event->setDropAction(Qt::MoveAction);
             event->accept();
         } else {
             event->acceptProposedAction();
         }
     } else if (event->mimeData()->hasText()) {
         event->acceptProposedAction();
     } else {
         event->ignore();
     }
 }

 void WhiteBoard::dragMoveEvent(QDragMoveEvent *event)
 {
     if (event->mimeData()->hasFormat("*/*")) {
         if (children().contains(event->source())) {
             event->setDropAction(Qt::MoveAction);
             event->accept();
         } else {
             event->acceptProposedAction();
         }
     } else if (event->mimeData()->hasText()) {
         event->acceptProposedAction();
     } else {
         event->ignore();
     }
 }

 void WhiteBoard::dropEvent(QDropEvent *event)
 {
     if (event->mimeData()->hasFormat("*/*")) {
         const QMimeData *mime = event->mimeData();
         QByteArray itemData = mime->data("application/x-fridgemagnet");
         QDataStream dataStream(&itemData, QIODevice::ReadOnly);

         QString text;
         QPoint offset;
         //dataStream >> text >> offset;
        dataStream >> offset;

         //Items *newLabel = new Items(this);
         //newLabel->move(event->pos() - offset);
         //newLabel->show();

           //tmp->move(event->pos() - offset);
         tmp->move(0,0);
           tmp->show();


qDebug() << "finalement : " << tmp->parentWidget();
         if (children().contains(event->source())) {
             event->setDropAction(Qt::MoveAction);
             event->accept();
         } else {
             event->acceptProposedAction();
         }
     } else if (event->mimeData()->hasText()) {

         QStringList pieces = event->mimeData()->text().split(QRegExp("\\s+"),
                              QString::SkipEmptyParts);
         QPoint position = event->pos();

         foreach (QString piece, pieces) {
               tmp->move(position);
           tmp->show();

         //    Items *newLabel = new Items(this);
           //  newLabel->move(position);
             //newLabel->show();

             position += QPoint(tmp->width(), 0);
         }

         event->acceptProposedAction();

     } else {
         event->ignore();
     }
 }
