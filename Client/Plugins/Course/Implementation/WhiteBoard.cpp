/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "WhiteBoard.h"

#include <QDebug>
#include <QPushButton>

#include "LessonDocument.h"
#include "Items.h"

#include "../LessonManager/Implementation/Lesson.h"

WhiteBoard::WhiteBoard(WhiteBoardData* wbd, QHash<QString, IDocumentController *> controllers, LessonModel *model, UserData *user)
        : _controllers(controllers), model(model), _user(user)
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
	setStyleSheet("QFrame[whiteboard=\"true\"] { border: 0px; background: qlineargradient(spread:pad, x1:1, y1:1, x2:0, y2:0.0113636, stop:0 rgba(202, 225, 229, 255), stop:0.494318 rgba(255, 255, 255, 255)); } ");
	layout->addWidget(displayArea, 1, 0);
    this->posInDoc = 0;

    QPalette p(this->palette());
    p.setColor(QPalette::Background, Qt::white);
    this->setPalette(p);

    qDebug() << "connect";
    if (_user->level() == LEVEL_STUDENT)
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
    if (_user->level() == LEVEL_TEACHER)
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
                    Items *item = new Items(displayArea, this, lesson, id, type, title);

                    QWidget *docWidget;
                    docWidget = this->_controllers[type]->createDocumentWidget(doc);
                    QPoint offset(0, dock->height());
                    item->move(event->pos() - offset);
                    if (docWidget)
                    {
                            docWidget->lower();
                            item->show();
                            item->setMainWidget(docWidget);
                            item->resize(QSize(200, 200));
                    }
                    if (event->pos().y() < dock->size().height())
                    {
                            item->moveToDock();
                    }
                    fillList(displayArea, wbdata->items());
                    wbdata->save();
            }
            else
                    qWarning()<< tr("WhiteBoard::dropEvent: unable to find a controller for") << type << tr("type.");
        }
    }
    else
    {
        QString text;
        QPoint offset(event->mimeData()->property("hotspot").toPoint());
        offset.setY(offset.y() + dock->height());
        tmp->move(event->pos() - offset);
        tmp->show();
        tmp->parentWidget()->repaint();
        event->acceptProposedAction();
        fillList(displayArea, wbdata->items());
        wbdata->save();
    }
 }

 void	WhiteBoard::update()
 {
        const QObjectList& itemList = displayArea->children();
	WhiteBoardItemList& list = wbdata->items();
	WhiteBoardItemList::const_iterator it;
	QObjectList::const_iterator it2;
        qDebug() << "wbdata update: " << list.count();
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
                                qDebug() << "found widget !!";
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
                                        Items *item = new Items(displayArea, this, model->getLesson(it->idLesson()), document->getId(),
											document->getParameters().value("type").toString(),
											document->getParameters().value("title").toString());
					qDebug() << "creating item";
					QWidget *docWidget;
                                        docWidget = this->_controllers[document->getType()]->createDocumentWidget(document);
                                        item->move(it->left(), it->top());
                                        item->resize(QSize(it->width(), it->height()));
					if (docWidget)
					{
						docWidget->lower();
                                                item->setMainWidget(docWidget);
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
