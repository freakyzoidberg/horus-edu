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
#ifndef WHITEBOARDOBJECT_H
#define WHITEBOARDOBJECT_H

#include <QFrame>
#include <QGridLayout>
#include <QAction>
#include <QImage>
#include <QLabel>

#include "WhiteBoard.h"
#include "../../LessonManager/IDocumentController.h"
#include "../../LessonManager/ILesson.h"
#include "../../../../Common/UserData.h"

enum WbBorderPos {TOP_LEFT, TOP, TOP_RIGHT, LEFT, RIGHT, BOTTOM_LEFT, BOTTOM, BOTTOM_RIGHT, UNDEFINED};

class WhiteboardObject : public QFrame
{
    Q_OBJECT
public:
    WhiteboardObject(QWidget *parent, WhiteBoard *wb, ILessonDocument *document, IDocumentController *controller, UserData *user);
    ~WhiteboardObject();

    bool				isDocked();
	bool				isSynced();
	ILessonDocument*	getDocument();
	ILesson*			getLesson();
	void				setSize(int w, int h);
	void				setSize(const QSize& sz);
	WhiteBoard*			getBoard();
	int							getCommandId() { return _commandId; }
	WhiteBoardItem::Command		getCommand() { return _command; }
	qint64						getArgument() { return _argument; }

signals:
	void			setSync(bool);
	void			command(quint32, WhiteBoardItem::Command, qint64);

public slots:
    void            switchDockMode();
	void			switchSync(bool);
	void			setCommand(quint32 id, WhiteBoardItem::Command command, qint64 argument);

protected:
    void            mousePressEvent(QMouseEvent *event);
    void            mouseMoveEvent(QMouseEvent *event);
    void            mouseReleaseEvent(QMouseEvent *event);

private:
    WhiteBoard*     _board;
    QWidget*        _mainWidget;
    QAction*		_dockAction;
	QAction*		_closeAction;
	QAction*		_syncAction;
    bool            _isDocked;
	bool			_isMoving;
	bool			_isSynced;
    QGridLayout*	_layout;
	QPoint			_savedPos;

	ILessonDocument*		_document;
	ILesson*				_lesson;
	IDocumentController*	_controller;
	UserData*				_user;

	quint32				_commandId;
	WhiteBoardItem::Command	_command;
	qint64				_argument;
};

class LoadIcon : public QLabel
{
public:
	LoadIcon();

protected:
	void	timerEvent(QTimerEvent *event);

private:
	static bool _imgLoaded;
	static QImage	_images[8];
	int _current;
};

#endif // WHITEBOARDOBJECT_H
