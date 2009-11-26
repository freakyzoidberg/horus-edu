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
#ifndef WHITEBOARD_H
#define WHITEBOARD_H

#include <QObject>
#include <QWidget>
#include <QDragEnterEvent>
#include <QPushButton>
#include <QToolBar>
#include <QHash>
#include <QVector>
#include <QToolBox>
#include <QGridLayout>

#include "../../LessonManager/IDocumentController.h"
#include "../../LessonManager/ILesson.h"
#include "../../LessonManager/LessonModel.h"
#include "../../../../Common/FileDataPlugin.h"
#include "../../../../Common/UserData.h"
#include "../../../../Common/DataImplementations/WhiteBoardData/WhiteBoardData.h"

class Items;

class WhiteBoard : public QWidget
{
    Q_OBJECT

public:
    WhiteBoard(WhiteBoardData* wb, QHash<QString, IDocumentController *> controllers, LessonModel *model, UserData *user);
     void   setTmp(Items *);
     Items  *getTmp();
     void   setPosInDoc(int posInDoc);
     int    getPosInDoc();
     QToolBar *dock;
     QVector<QPushButton *>   button;
     QHash<QString, IDocumentController *>  getControllers();

protected:
     void dragEnterEvent(QDragEnterEvent *event);
     void dragMoveEvent(QDragMoveEvent *event);
     void dropEvent(QDropEvent *event);
     QHash<QString, IDocumentController *> _controllers;

public slots:
	void	update();

private:
	ILessonDocument		*findDocument(int lessonId, int documentId);
    void                fillList(QObject* data, WhiteBoardItemList&);

 private:
    Items           *tmp;
    int             posInDoc;
    WhiteBoardData* wbdata;
	QGridLayout     *layout;
	QWidget			*displayArea;
	LessonModel		*model;
        UserData*               _user;
};

#endif // WHITEBOARD_H
