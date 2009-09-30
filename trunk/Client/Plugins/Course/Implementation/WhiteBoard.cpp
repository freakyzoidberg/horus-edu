#include "WhiteBoard.h"

#include <QDebug>
#include <QPushButton>

#include "LessonDocument.h"
#include "Items.h"

WhiteBoard::WhiteBoard(WhiteBoardData* wbd, QHash<QString, IDocumentController *> controllers, ILesson *lesson)
	: _controllers(controllers), lesson(lesson)
{
    wbdata = wbd;
    setAcceptDrops(true);
    setAutoFillBackground(true);
    layout = new QVBoxLayout(this);

    this->dock = new QToolBar(this);
    this->dock->setGeometry(0, 0, this->geometry().width(), 20);
   // this->dock->addWidget(this->dock);
    this->posInDoc = 0;

    QPalette p(this->palette());
    p.setColor(QPalette::Background, Qt::white);
    this->setPalette(p);

    QObject::connect(wbdata, SIGNAL(updated()), this, SLOT(update()));

    QPushButton *testicule = new QPushButton("edtion pdf", this);
    connect(testicule, SIGNAL(clicked()), this, SLOT(calltheshot()));
}

void    WhiteBoard::calltheshot()
{
    QHash<QString, QVariant> parameters;
    parameters.insert("page", QVariant(0));
    Items *item = new Items(this, 1, "Pdf", "testpdf");
    QFile *merde = new QFile("/tmp/17");
    ILessonDocument *doc = new LessonDocument(this, 1, "cmbdtc", "Pdf", "null", parameters);
    doc->setId(1);
    QWidget *docWidget = this->_controllers["Pdf"]->editDocument(merde, item, doc);
    docWidget->lower();
    item->repaint();
    item->show();
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
                                Items *item = new Items(this, id, type, title);

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
			if (item && item->getId() == it->id())
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
			ILessonDocument* document = findDocument(lesson);
			if (document)
			{
				if (this->_controllers.contains(document->getType()))
				{
                                        Items *item = new Items(this, document->getId(),
                                                                document->getParameters().value("type").toString(),
                                                                document->getParameters().value("title").toString());
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
				if (item->getId() == it->id())
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

 ILessonDocument*	WhiteBoard::findDocument(ILessonData* data)
 {
	 if (data)
	 {
		QObjectList::const_iterator it;
		for (it = data->children().begin(); it != data->children().end(); it++)
		{
			if (qobject_cast<ILessonDocument *>(*it))
				return qobject_cast<ILessonDocument *>(*it);
			ILessonDocument *document = findDocument(qobject_cast<ILessonData *>(*it));
			if (document)
                                return document;
		}
	}
	return NULL;
 }

void	WhiteBoard::fillList(QObject* data, WhiteBoardItemList& list)
{
	if (data)
	 {
		QObjectList::const_iterator it;
		for (it = data->children().begin(); it != data->children().end(); it++)
		{
			if (qobject_cast<Items *>(*it))
			{
				Items* item = qobject_cast<Items *>(*it);
				list.append(WhiteBoardItem(item->getId(), item->x(), item->y(), item->width(), item->height(), false));
			}
		}
	}
}

QHash<QString, IDocumentController *>  WhiteBoard::getControllers()
{
    return this->_controllers;
}
