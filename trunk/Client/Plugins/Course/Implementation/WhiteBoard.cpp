#include "WhiteBoard.h"
#include "Items.h"
#include <QDebug>
WhiteBoard::WhiteBoard()
{
    setAcceptDrops(true);
    setAutoFillBackground(false);
    this->dock = new QDockWidget("Magic doc", this);
    this->dock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
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
           tmp->closeItem->raise();
           tmp->closeItem->show();
           tmp->setVisible(true);
           tmp->parentWidget()->repaint();
           tmp->closeItem->parentWidget()->repaint();
           event->acceptProposedAction();


           //Position pour le generateur du fichier de position

           qDebug() << "items in WhiteBoard : "<< this->children().count();

 }
