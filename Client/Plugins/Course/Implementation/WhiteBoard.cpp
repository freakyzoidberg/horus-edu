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
#include <QLabel>

#include "LessonDocument.h"
#include "WhiteboardObject.h"

#include "../LessonManager/Implementation/Lesson.h"

WhiteBoard::WhiteBoard(WhiteBoardData* wbd, QHash<QString, IDocumentController *>& controllers, LessonModel *model, UserData *user)
        : _controllers(controllers), _model(model), _user(user), _wbdata(wbd)
{
    setAutoFillBackground(true);
	setAcceptDrops(true);

	_layout = new QGridLayout(this);
	_layout->setMargin(0);
	_layout->setSpacing(0);

    _dock = new QToolBar(this);
	_dock->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	if (_user->level() == LEVEL_TEACHER)
	{
		_dock->setStyleSheet("font-family: \"Tohoma\"; font-size: 10px; font-weight: bold; color: white;");
		QAction* closeAction = new QAction(QIcon(":/close-item.png"), "", _dock);
		_dock->addAction(closeAction);
	}
	else
	{
		_dock->setStyleSheet("QToolBar { background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0.318182 rgba(127, 127, 127, 255), stop:0.380682 rgba(100, 100, 100, 255)); spacing: 0px; margin: 0px; border: 0px; max-height: 20px; min-height: 20px; } ");
		QAction* closeAction = new QAction(QIcon(":/close-item.png"), "", _dock);
		_dock->addAction(closeAction);
		QLabel* title = new QLabel("  History class, 6eme (Adrien Grandemange)");
		title->setStyleSheet("QLabel {font-family: \"Tohoma\"; font-size: 10px; font-weight: bold; color: white; }");
		_dock->addWidget(title);
	}
	_layout->addWidget(_dock, 0, 0);
	_displayArea = new QFrame(this);
	_displayArea->setProperty("whiteboard", QVariant(true));
	setStyleSheet("QFrame[whiteboard=\"true\"] { border: 0px; background: qlineargradient(spread:pad, x1:1, y1:1, x2:0, y2:0.0113636, stop:0 rgba(202, 225, 229, 255), stop:0.494318 rgba(255, 255, 255, 255)); } ");
	_layout->addWidget(_displayArea, 1, 0);

	update();

    if (_user->level() == LEVEL_STUDENT)
	{
        QObject::connect(_wbdata, SIGNAL(updated()), this, SLOT(update()));
	}
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

QToolBar*	WhiteBoard::getDock()
{
	return _dock;
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
            ILessonDocument *doc = _model->getLessonDocument(lessonid, id);
			WhiteboardObject *wbObject;
            if (this->_controllers.contains(type))
            {
					wbObject = new WhiteboardObject(_displayArea, this, doc, this->_controllers[type], _user);
            }
            else
			{
                    wbObject = new WhiteboardObject(_displayArea, this, doc, NULL, _user);
			}
			QPoint offset(0, _dock->height());
            wbObject->move(event->pos() - offset);
            if (event->pos().y() < _dock->size().height())
            {
				wbObject->switchDockMode();
            }
            notifyChange();
			connect(wbObject, SIGNAL(destroyed()), this, SLOT(notifyChange()));
        }
    }
 }

 void	WhiteBoard::update()
 {
	 const QObjectList& wbObjectList = _displayArea->children();
	 WhiteBoardItemList list = _wbdata->items();
	 WhiteBoardItemList::const_iterator it;
	 QObjectList::const_iterator it2;
	 for (it = list.begin(); it != list.end(); it++)
	 {
		 bool found = false;
		 for (it2 = wbObjectList.begin(); it2 != wbObjectList.end(); it2++)
		 {
			 WhiteboardObject* wbObject = qobject_cast<WhiteboardObject *>(*it2);
			 if (wbObject && wbObject->getLesson()->getId() == it->idLesson() && wbObject->getDocument()->getId() == it->idSection())
			 {
				 wbObject->move(it->left(), it->top());
				 wbObject->setSize(it->width(), it->height());
				 if (it->docked())
				 {
					 wbObject->hide();
				 }
				 else
				 {
					 wbObject->show();
				 }
				 found = true;
				 break;
			 }
		 }
		 if (!found)
		 {
			 ILessonDocument* document = _model->getLessonDocument(it->idLesson(), it->idSection());
			 if (document)
			 {
				 WhiteboardObject *wbObject;
				 if (this->_controllers.contains(document->getType()))
				 {
					 wbObject = new WhiteboardObject(_displayArea, this, document, _controllers[document->getType()], _user);
				 }
				 else
				 {
					 wbObject = new WhiteboardObject(_displayArea, this, document, NULL, _user);
				 }
				 wbObject->move(it->left(), it->top());
				 wbObject->setSize(it->width(), it->height());
				 if (it->docked())
				 {
					 wbObject->hide();
				 }
				 else
				 {
					 wbObject->show();
				 }
			 }
		 }
	 }
	 for (it2 = wbObjectList.begin(); it2 != wbObjectList.end(); it2++)
	 {
		 WhiteboardObject* wbObject = qobject_cast<WhiteboardObject *>(*it2);
		 if (wbObject)
		 {
			 bool found = false;
			 for (it = list.begin(); it != list.end(); it++)
			 {
				 if (wbObject->getLesson()->getId() == it->idLesson() && wbObject->getDocument()->getId() == it->idSection())
				 {
					 found = true;
					 break;
				 }
			 }
			 if (!found)
			 {
				 wbObject->close();
			 }
		 }
	 }
 }

void	WhiteBoard::notifyChange()
{
	if (_user->level() == LEVEL_TEACHER)
	{
		WhiteBoardItemList& list = _wbdata->items();
		list.clear();
		QObjectList::const_iterator it;
		for (it = _displayArea->children().begin(); it != _displayArea->children().end(); it++)
		{
			if (qobject_cast<WhiteboardObject *>(*it))
			{
				WhiteboardObject* wbObject = qobject_cast<WhiteboardObject *>(*it);
				list.append(WhiteBoardItem(wbObject->getLesson()->getId(), wbObject->getDocument()->getId(), wbObject->x(), wbObject->y(), wbObject->width(), wbObject->height(), wbObject->isDocked()));
			}
		}
		_wbdata->save();
	}
}
