#include "WhiteBoard.h"

#include <QDebug>
#include <QPushButton>

#include "LessonDocument.h"
#include "Items.h"

#include "../LessonManager/Implementation/Lesson.h"

WhiteBoard::WhiteBoard(WhiteBoardData* wbd, QHash<QString, IDocumentController *> controllers, LessonModel *model)
	: _controllers(controllers), model(model)
{
    wbdata = wbd;
    setAutoFillBackground(true);
	setAcceptDrops(true);
	layout = new QGridLayout(this);
	layout->setMargin(0);
	layout->setSpacing(0);

    this->dock = new QToolBar(this);
	layout->addWidget(this->dock, 0, 0);
	displayArea = new QFrame(this);
	displayArea->setProperty("whiteboard", QVariant(true));
	setStyleSheet("QFrame[whiteboard=\"true\"] { border: 2px solid black; border-top: 0px; border-radius: 4px; } ");
	layout->addWidget(displayArea, 1, 0);
    this->posInDoc = 0;

    QPalette p(this->palette());
    p.setColor(QPalette::Background, Qt::white);
    this->setPalette(p);

    QObject::connect(wbdata, SIGNAL(updated()), this, SLOT(update()));
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
			int lessonid;
			int id;
			QString title;
			QString type;
			QString content;
			int count;
			QString key;
			QVariant value;
			QHash<QString, QVariant> parameters;
			stream >> lessonid >> id >> title >> type >> content >> count;
			for (int i = 0; i < count; i++)
			{
				stream >> key >> value;
				parameters[key] = value;
			}
			ILesson *lesson = model->getLesson(lessonid);
			ILessonDocument *doc = model->getLessonDocument(lessonid, id);
			if (this->_controllers.contains(type))
			{
				Items *item = new Items(this, lesson, id, type, title);

				QWidget *docWidget;
				docWidget = this->_controllers[type]->createDocumentWidget(item, doc);
				item->move(event->pos());
				item->setWindowFlags(Qt::SubWindow);
				if (docWidget)
				{
					docWidget->lower();
					item->show();
					item->resize(docWidget->size());
					item->repaint();
				}
				if (event->pos().y() < dock->size().height())
				{
					item->moveToDock();
				}
				fillList(this, wbdata->items());
				wbdata->save();
			}
			else
				qWarning()<< tr("WhiteBoard::dropEvent: unable to find a controller for") << type << tr("type.");
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

			fillList(this, wbdata->items());
			wbdata->save();
	}
 }

 void	WhiteBoard::update()
 {
	const QObjectList& itemList = children();
	WhiteBoardItemList& list = wbdata->items();
	WhiteBoardItemList::const_iterator it;
	QObjectList::const_iterator it2;
	for (it = list.begin(); it != list.end(); it++)
	{
		bool found = false;
		for (it2 = itemList.begin(); it2 != itemList.end(); it2++)
		{
			Items* item = qobject_cast<Items *>(*it2);
			if (item && item->getId() == it->idSection() && item->getLesson()->getId() == it->idLesson())
			{
				item->setGeometry(it->left(), it->top(), it->width(), it->height());
//				if (it->docked())
//					item->moveToDock();
//				else
//					item->restore();
				found = true;
				break;
			}
		}
		if (!found)
		{
			qDebug() << "new widget in whiteboard";
			ILessonDocument* document = findDocument(it->idLesson(), it->idSection());
			if (document)
			{
				qDebug() << "found document";
				if (this->_controllers.contains(document->getType()))
				{
					Items *item = new Items(this, model->getLesson(1), document->getId(),
											document->getParameters().value("type").toString(),
											document->getParameters().value("title").toString());
					qDebug() << "creating item";
					QWidget *docWidget;
					docWidget = this->_controllers[document->getType()]->createDocumentWidget(item, document);
					item->setGeometry(it->left(), it->top(), it->width(), it->height());
					if (docWidget)
					{
						docWidget->lower();

                                                item->show();

						item->repaint();
					}
				}
				else
					qWarning()<< tr("WhiteBoard::dropEvent: unable to find a controller for") << document->getType() << tr("type.");
			}
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
				if (item->getLesson()->getId() == it->idLesson() && item->getId() == it->idSection())
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

 ILessonDocument*	WhiteBoard::findDocument(int lessonId, int documentId)
 {
	return model->getLessonDocument(lessonId, documentId);
 }

void	WhiteBoard::fillList(QObject* data, WhiteBoardItemList& list)
{
	list.clear();
	if (data)
	 {
		QObjectList::const_iterator it;
		for (it = data->children().begin(); it != data->children().end(); it++)
		{
			if (qobject_cast<Items *>(*it))
			{
				Items* item = qobject_cast<Items *>(*it);
				list.append(WhiteBoardItem(item->getLesson()->getId(), item->getId(), item->x(), item->y(), item->width(), item->height(), false));
			}
		}
	}
}

QHash<QString, IDocumentController *>  WhiteBoard::getControllers()
{
    return this->_controllers;
}
