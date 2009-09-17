#include "WhiteBoard.h"

#include <QDebug>

#include "LessonDocument.h"
#include "Items.h"

WhiteBoard::WhiteBoard(FileDataPlugin *filePlugin, QHash<QString, IDocumentController *> controllers, ILesson *lesson)
	: _controllers(controllers), wbdata(filePlugin, 51), lesson(lesson)
{
    setAcceptDrops(true);
    setAutoFillBackground(true);
    this->dock = new QToolBar(this);
    this->dock->setGeometry(0, 0, this->geometry().width(), 20);
    //this->setGeometry(
    this->posInDoc = 0;
	QPalette p(this->palette());
	p.setColor(QPalette::Background, Qt::white);
	this->setPalette(p);
	QObject::connect(&wbdata, SIGNAL(remoteUpdate(WhiteBoardItemList)), SLOT(update(WhiteBoardItemList)));
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
			int id;
			QString title;
			QString type;
			QString content;
			int count;
			QString key;
			QVariant value;
			QHash<QString, QVariant> parameters;
			stream >> id >> title >> type >> content >> count;
			for (int i = 0; i < count; i++)
			{
				stream >> key >> value;
				parameters[key] = value;
			}
			ILessonDocument *doc = new LessonDocument(this, id, title, type, content, parameters);
			if (this->_controllers.contains(type))
			{
				Items *item = new Items(this, id);
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

 void	WhiteBoard::update(const WhiteBoardItemList& list)
 {
	const QObjectList& itemList = children();
	WhiteBoardItemList::const_iterator it;
	QObjectList::const_iterator it2;
	for (it = list.begin(); it != list.end(); it++)
	{
		bool found = false;
		for (it2 = itemList.begin(); it2 != itemList.end(); it2++)
		{
			Items* item = qobject_cast<Items *>(*it2);
			if (item && item->getId() == it->getId())
			{
				item->setGeometry(it->getX(), it->getY(), it->getWidth(), it->getHeight());
				if (it->docked())
					item->moveToDock();
				else
					item->restore();
				found = true;
				break;
			}
		}
		if (!found)
		{
//			bool lfound = false;
//			while (!lfound)
//			{
//				ILessonData *data = lesson;
//				lesson->children()
//			}
		}
	}
	for (it2 = itemList.begin(); it2 != itemList.end(); it2++)
	{
		Items* item = qobject_cast<Items *>(*it2);
		if (item)
		{
			bool found = false;
			for (it = list.begin(); it != list.end(); it++)
			{
				if (item->getId() == it->getId())
				{
					found = true;
					break;
				}
			}
			if (!found)
				item->close();
		}
	}
 }
