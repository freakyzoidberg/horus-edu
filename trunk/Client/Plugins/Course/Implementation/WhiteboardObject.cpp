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

#include <QToolBar>
#include <QIcon>
#include <QLabel>

#include "WhiteboardObject.h"

WhiteboardObject::WhiteboardObject(QWidget *parent, WhiteBoard *wb, ILessonDocument *document, IDocumentController *controller, UserData *user) : QFrame(parent), _board(wb), _document(document), _controller(controller), _user(user)
{
    _layout = new QGridLayout(this);

	QToolBar* toolBar = new QToolBar();
	toolBar->setStyleSheet("QToolBar { background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0.318182 rgba(127, 127, 127, 255), stop:0.380682 rgba(100, 100, 100, 255)); spacing: 0px; margin: 0px; border: 0px; max-height: 20px; min-height: 20px; } ");
	_layout->addWidget(toolBar, 0, 0);
	if (_user->level() == LEVEL_TEACHER)
	{
		_closeAction = new QAction(QIcon(":/close.png"), "", toolBar);
		toolBar->addAction(_closeAction);
		_dockAction = new QAction(QIcon(":/fleche_haut_vert.png"), document->getTitle(), toolBar);
		toolBar->addAction(_dockAction);
	}
	QLabel* title = new QLabel("  " + document->getTitle());
	title->setStyleSheet("QLabel {font-family: \"Tohoma\"; font-size: 10px; font-weight: bold; color: white; }");
	toolBar->addWidget(title);
    _layout->setMargin(0);
    _layout->setSpacing(0);

	setAttribute(Qt::WA_DeleteOnClose);
	setStyleSheet("WhiteboardObject {border: 4px solid #888888; border-radius: 8px; }");
	if (_user->level() == LEVEL_TEACHER)
	{
		connect(_closeAction, SIGNAL(triggered()), this, SLOT(close()));
		connect(_dockAction, SIGNAL(triggered()), this, SLOT(switchDockMode()));
	}
    setMinimumHeight(80);
    setMinimumWidth(120);

    _isDocked = false;
    _isMoving = false;

    setWindowFlags(Qt::SubWindow);
	setAcceptDrops(true);

	ILessonData* ldata = static_cast<ILessonData *>(_document->parent());
	do
	{
		_lesson = dynamic_cast<ILesson *>(ldata);
		if (_lesson != NULL)
			break;
		ldata = static_cast<ILessonData *>(ldata->parent());
	} while (true);

	if (_controller != NULL)
	{
		_mainWidget = _controller->createDocumentWidget(_document);
	}
	else
	{
		_mainWidget = new QLabel("Unhandled object.");
	}
	_layout->addWidget(_mainWidget, 1, 0);

	show();
}

WhiteboardObject::~WhiteboardObject()
{
}

bool    WhiteboardObject::isDocked()
{
    return _isDocked;
}

ILessonDocument*	WhiteboardObject::getDocument()
{
	return _document;
}

ILesson*			WhiteboardObject::getLesson()
{
	return _lesson;
}

void    WhiteboardObject::mouseReleaseEvent(QMouseEvent *event)
{
	_isMoving = false;
	_board->notifyChange();
}

void WhiteboardObject::mouseMoveEvent(QMouseEvent *event)
{
	if (_isMoving)
	{
		QWidget* par = static_cast<QWidget *>(parent());
		QPoint targetPos = pos() + (event->pos() - _savedPos);
		if (targetPos.x() < 0)
			targetPos.setX(0);
		if (targetPos.y() < 0)
			targetPos.setY(0);
		if (targetPos.x() + width() > par->width())
			targetPos.setX(par->width() - width());
		if (targetPos.y() + height() > par->height())
			targetPos.setY(par->height() - height());
		move(targetPos);
	}
}

void WhiteboardObject::mousePressEvent(QMouseEvent *event)
{
	if (_user->level() == LEVEL_TEACHER)
	{
		_isMoving = true;
		_savedPos = event->pos();
	}
}

void	WhiteboardObject::resizeEvent(QResizeEvent *event)
{
	event->accept();
	_board->notifyChange();
}

void    WhiteboardObject::switchDockMode()
{
	if (isHidden())
	{
		show();
		_dockAction->setIcon(QIcon(":/fleche_haut_vert.png"));
		_board->getDock()->removeAction(_dockAction);
		_isDocked = false;
	}
	else
	{
		hide();
		_dockAction->setIcon(QIcon(":/fleche_bas_vert.png"));
		_board->getDock()->addAction(_dockAction);
		_isDocked = true;
	}
	_board->notifyChange();
}
