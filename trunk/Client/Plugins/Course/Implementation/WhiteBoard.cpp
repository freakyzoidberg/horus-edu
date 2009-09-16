#include "WhiteBoard.h"

#include <QDebug>

#include "LessonDocument.h"
#include "Items.h"

WhiteBoard::WhiteBoard(FileDataPlugin *filePlugin, QHash<QString, IDocumentController *> controllers)
    : _controllers(controllers), wbdata(filePlugin, 40)
{
    setAcceptDrops(true);
    setAutoFillBackground(true);
    this->dock = new QToolBar(this);
  //  this->dock->setAllowedAreas(Qt::BottomDockWidgetArea);
  //  this->dock->setFeatures(QDockWidget::DockWidgetMovable);

    //Qt::BottomDockWidgetArea

    this->dock->setGeometry(0, 0, this->geometry().width(), 20);
    //this->setGeometry(
    this->posInDoc = 0;
	QPalette p(this->palette());
	p.setColor(QPalette::Background, Qt::white);
	this->setPalette(p);
}

void   WhiteBoard::setTmp(Items *item)
{
    tmp = item;
}


Items  *WhiteBoard::getTmp()
{
    return tmp;
}

void    WhiteBoard::setPosInDoc(int posInDoc)
{
    this->posInDoc = posInDoc;
}

int     WhiteBoard::getPosInDoc()
{
    return this->posInDoc;
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
	const QMimeData *mime = event->mimeData();
	if (mime->hasFormat("application/vnd.horus.lessondocument.list"))
	{
		QByteArray encodedData = mime->data("application/vnd.horus.lessondocument.list");
		QDataStream stream(&encodedData, QIODevice::ReadOnly);
		QStringList newItems;
		while (!stream.atEnd())
		{
			QString title;
			QString type;
			QString content;
			int count;
			QString key;
			QVariant value;
			QHash<QString, QVariant> parameters;
			stream >> title >> type >> content >> count;
			for (int i = 0; i < count; i++)
			{
				stream >> key >> value;
				parameters[key] = value;
			}
			ILessonDocument *doc = new LessonDocument(this, title, type, content, parameters);
			if (this->_controllers.contains(type))
			{
				Items *item = new Items(this);
				QWidget *docWidget;
				docWidget = this->_controllers[type]->createDocumentWidget(item, doc);
				item->move(event->pos());
				if (docWidget)
				{
					docWidget->lower();
					item->show();
					item->resize(docWidget->size());
					item->repaint();
				}
			}
			else
				qWarning()<< "WhiteBoard::dropEvent: unable to find a controller for" << type << "type.";
		}
	}
	else
	{
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
           //tmp->raise();
           tmp->show();
 //          tmp->closeItem->raise();
   //        tmp->closeItem->show();
           tmp->setVisible(true);
           tmp->parentWidget()->repaint();
     //      tmp->closeItem->parentWidget()->repaint();
           event->acceptProposedAction();


           //Position pour le generateur du fichier de position

           qDebug() << "items in WhiteBoard : "<< this->children().count();
	}
 }
