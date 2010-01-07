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

class WbBorder : public QFrame
{
public:
	WbBorder(WbBorderPos p, bool teacher, WhiteboardObject *obj) : _position(p), _teacher(teacher), _isResizing(false), _obj(obj)
	{
		_bgUrl[TOP_LEFT] = ":/Ui/wb-tl.png";
		_bgUrl[TOP] = ":/Ui/wb-top.png";
		_bgUrl[TOP_RIGHT] = ":/Ui/wb-tr.png";
		_bgUrl[LEFT] = ":/Ui/wb-left.png";
		_bgUrl[RIGHT] = ":/Ui/wb-right.png";
		_bgUrl[BOTTOM_LEFT] = ":/Ui/wb-bl.png";
		_bgUrl[BOTTOM] = ":/Ui/wb-bottom.png";
		_bgUrl[BOTTOM_RIGHT] = ":/Ui/wb-br.png";
		setMinimumSize(4, 4);
		if (_position == LEFT || _position == RIGHT)
		{
			setMaximumWidth(4);
			if (_teacher)
				setCursor(Qt::SizeHorCursor);
		}
		else if (_position == TOP || _position == BOTTOM)
		{
			setMaximumHeight(4);
			if (_teacher)
				setCursor(Qt::SizeVerCursor);
		}
		else
		{
			setMaximumSize(4, 4);
			if (_teacher)
			{
				switch (_position)
				{
				case TOP_LEFT:
				case BOTTOM_RIGHT:
					setCursor(Qt::SizeFDiagCursor);
					break;
				case TOP_RIGHT:
				case BOTTOM_LEFT:
					setCursor(Qt::SizeBDiagCursor);
					break;
				}
			}
		}
		QString style = "QFrame { border: 0px; padding: 0px; marging: 0px; background: url(" + _bgUrl[_position] + "); }";
		setStyleSheet(style);
	}

	void	mousePressEvent(QMouseEvent *event)
	{
		if (_teacher)
		{
			_isResizing = true;
			_lastPos = event->globalPos();
		}
	}

    void	mouseMoveEvent(QMouseEvent *event)
	{
		if (_teacher)
		{
			QPoint diff = event->globalPos() - _lastPos;
			int w = diff.x();
			int h = diff.y();
			QSize targetSz = _obj->size();
			QPoint targetPos = _obj->pos();
			switch (_position)
			{
			case TOP_LEFT:
				targetSz -= QSize(w, h);
				targetPos += QPoint(w, h);
				break;
			case TOP:
				targetSz -= QSize(0, h);
				targetPos += QPoint(0, h);
				break;
			case TOP_RIGHT:
				targetSz -= QSize(-w, h);
				targetPos += QPoint(0, h);
				break;
			case LEFT:
				targetSz -= QSize(w, 0);
				targetPos += QPoint(w, 0);
				break;
			case RIGHT:
				targetSz += QSize(w, 0);
				break;
			case BOTTOM_LEFT:
				targetSz += QSize(-w, h);
				targetPos += QPoint(w, 0);
				break;
			case BOTTOM:
				targetSz += QSize(0, h);
				break;
			case BOTTOM_RIGHT:
				targetSz += QSize(w, h);
				break;
			}
			if (targetPos.x() < 0 || targetSz.width() < 150 || targetPos.x() + targetSz.width() > _obj->getBoard()->width())
			{
				targetSz.setWidth(_obj->width());
				targetPos.setX(_obj->x());
			}
			if (targetPos.y() < 0 || targetSz.height() < 100 || targetPos.y() + targetSz.height() > _obj->getBoard()->height() - _obj->getBoard()->getDock()->height())
			{
				targetSz.setHeight(_obj->height());
				targetPos.setY(_obj->y());
			}
			_obj->setMaximumSize(targetSz);
			_obj->setGeometry(targetPos.x(), targetPos.y(), targetSz.width(), targetSz.height());
			_lastPos = event->globalPos();
		}
	}

    void	mouseReleaseEvent(QMouseEvent *event)
	{
		if (_teacher)
		{
			_isResizing = false;
			_obj->getBoard()->notifyChange();
		}
	}

private:
	WbBorderPos _position;
	QString _bgUrl[8];
	bool _teacher;
	bool _isResizing;
	WhiteboardObject* _obj;
	QPoint _lastPos;
};

WhiteboardObject::WhiteboardObject(QWidget *parent, WhiteBoard *wb, ILessonDocument *document, IDocumentController *controller, UserData *user) : QFrame(parent), _board(wb), _document(document), _controller(controller), _user(user), _syncAction(NULL)
{
    _layout = new QGridLayout(this);

	QToolBar* toolBar = new QToolBar();
	toolBar->setStyleSheet("QToolBar { background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0.318182 rgba(127, 127, 127, 255), stop:0.380682 rgba(100, 100, 100, 255)); spacing: 0px; margin: 0px; border: 0px; max-height: 20px; min-height: 20px; icon-size: 16px; } ");
	bool teacher = (_user->level() == LEVEL_TEACHER);
	_layout->addWidget(new WbBorder(TOP_LEFT, teacher, this), 0, 0, 1, 1);
	_layout->addWidget(new WbBorder(TOP, teacher, this), 0, 1, 1, 1);
	_layout->addWidget(new WbBorder(TOP_RIGHT, teacher, this), 0, 2, 1, 1);
	_layout->addWidget(new WbBorder(LEFT, teacher, this), 1, 0, 2, 1);
	_layout->addWidget(new WbBorder(RIGHT, teacher, this), 1, 2, 2, 1);
	_layout->addWidget(new WbBorder(BOTTOM_LEFT, teacher, this), 3, 0, 1, 1);
	_layout->addWidget(new WbBorder(BOTTOM, teacher, this), 3, 1, 1, 1);
	_layout->addWidget(new WbBorder(BOTTOM_RIGHT, teacher, this), 3, 2, 1, 1);
	_layout->addWidget(toolBar, 1, 1);
	if (_user->level() == LEVEL_TEACHER)
	{
		_closeAction = new QAction(QIcon(":/close-item.png"), "", toolBar);
		toolBar->addAction(_closeAction);
		if (_controller && _controller->supportsSync())
		{
			_syncAction = new QAction(QIcon(":/sync-item.png"), "", toolBar);
			_syncAction->setCheckable(true);
			toolBar->addAction(_syncAction);
		}
		_dockAction = new QAction(QIcon(":/fleche_haut_vert.png"), document->getTitle(), toolBar);
		toolBar->addAction(_dockAction);
	}
	QLabel* title = new QLabel("  " + document->getTitle());
	title->setStyleSheet("QLabel {font-family: \"Tohoma\"; font-size: 10px; font-weight: bold; color: white; }");
	toolBar->addWidget(title);
    _layout->setMargin(0);
    _layout->setSpacing(0);

	setAttribute(Qt::WA_DeleteOnClose);
	setStyleSheet("WhiteboardObject {border: 0px; padding: 0px; margin: 0px; }");
	if (_user->level() == LEVEL_TEACHER)
	{
		connect(_closeAction, SIGNAL(triggered()), this, SLOT(close()));
		if (_controller && _controller->supportsSync())
		{
			connect(_syncAction, SIGNAL(triggered(bool)), this, SLOT(switchSync(bool)));
		}
		connect(_dockAction, SIGNAL(triggered()), this, SLOT(switchDockMode()));
	}
    setMinimumSize(150, 100);
	setMaximumSize(200, 150);

    _isDocked = false;
    _isMoving = false;
	_isSynced = false;

	ILessonData* ldata = static_cast<ILessonData *>(_document->parent());
	do
	{
		QString classname = ldata->metaObject()->className();
		if (classname == "Lesson")
		{
			_lesson = static_cast<ILesson *>(ldata);
			break;
		}
		QObject *obj = ldata->parent();
		ldata = static_cast<ILessonData *>(obj);
	} while (true);

	if (_controller != NULL)
	{
		_mainWidget = _controller->createDocumentWidget(_document, new LoadIcon());
		if (_controller->supportsSync())
		{
			if (_user->level() == LEVEL_STUDENT)
			{
				connect(this, SIGNAL(setSync(bool)), _mainWidget, SLOT(switchSync(bool)));
				connect(this, SIGNAL(command(quint32, WhiteBoardItem::Command, qint64)), _mainWidget, SLOT(setCommand(quint32, WhiteBoardItem::Command, qint64)));
			}
			else
			{
				connect(_mainWidget, SIGNAL(command(quint32, WhiteBoardItem::Command, qint64)), this, SLOT(setCommand(quint32, WhiteBoardItem::Command, qint64)));
			}
		}
	}
	else
	{
		_mainWidget = new QFrame();
		_mainWidget->setStyleSheet(" QFrame { background-color: rgba(100, 100, 100, 255); } ");
		QGridLayout* mlayout = new QGridLayout();
		_mainWidget->setLayout(mlayout);
		QLabel* iconLabel = new QLabel();
		iconLabel->setAlignment(Qt::AlignCenter);
		iconLabel->setPixmap(QPixmap(":/Ui/noplugin.png"));
		QLabel* textLabel = new QLabel(tr("Unknown content"));
		textLabel->setAlignment(Qt::AlignCenter);
		textLabel->setStyleSheet("QLabel {font-family: \"Tohoma\"; font-size: 10px; font-weight: bold; color: white; }");
		mlayout->addWidget(iconLabel);
		mlayout->addWidget(textLabel);
	}
	_layout->addWidget(_mainWidget, 2, 1);

	show();
}

WhiteboardObject::~WhiteboardObject()
{
}

bool    WhiteboardObject::isDocked()
{
    return _isDocked;
}

bool    WhiteboardObject::isSynced()
{
    return _isSynced;
}

ILessonDocument*	WhiteboardObject::getDocument()
{
	return _document;
}

ILesson*			WhiteboardObject::getLesson()
{
	return _lesson;
}

void    WhiteboardObject::mouseReleaseEvent(QMouseEvent *)
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

void	WhiteboardObject::setSize(int w, int h)
{
	if (w < 150)
		w = 150;
	if (h < 100)
		h = 100;
	setMaximumSize(w, h);
	resize(w, h);
	_board->notifyChange();
}

void	WhiteboardObject::setSize(const QSize& sz)
{
	setSize(sz.width(), sz.height());
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

void	WhiteboardObject::switchSync(bool mode)
{
	_isSynced = mode;
	if (_user->level() == LEVEL_TEACHER)
	{
		if (_syncAction != NULL)
		{
			if (_syncAction->isChecked() != mode)
			{
				_syncAction->setChecked(true);
			}
			_board->notifyChange();
		}
	}
	else
	{
		if (_controller && _controller->supportsSync())
		{
			emit setSync(mode);
			emit command(_commandId, _command, _argument);
		}
	}
}

void	WhiteboardObject::setCommand(quint32 id, WhiteBoardItem::Command comm, qint64 argument)
{
	_commandId = id;
	_command = comm;
	_argument = argument;
	if (_isSynced)
	{
		if (_user->level() == LEVEL_TEACHER)
		{
			_board->notifyChange();
		}
		else
		{
			emit command(id, comm, argument);
		}
	}
}

WhiteBoard*		WhiteboardObject::getBoard()
{
	return _board;
}

LoadIcon::LoadIcon() : _current(0)
{
	if (_imgLoaded == false)
	{
		_images[0] = QImage(":/load0.png");
		_images[1] = QImage(":/load1.png");
		_images[2] = QImage(":/load2.png");
		_images[3] = QImage(":/load3.png");
		_images[4] = QImage(":/load4.png");
		_images[5] = QImage(":/load5.png");
		_images[6] = QImage(":/load6.png");
		_images[7] = QImage(":/load7.png");
	}
	setAlignment(Qt::AlignCenter);
	setPixmap(QPixmap::fromImage(_images[_current]));
}

void	LoadIcon::timerEvent(QTimerEvent *event)
{
	_current = (_current + 1) % 8;
	setPixmap(QPixmap::fromImage(_images[_current]));
}

bool LoadIcon::_imgLoaded = false;
QImage	LoadIcon::_images[8];
