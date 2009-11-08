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
#include "../../../../Common/DataImplementations/WhiteBoardData/WhiteBoardData.h"

class Items;

class WhiteBoard : public QWidget
{
    Q_OBJECT

public:
	 WhiteBoard(WhiteBoardData* wb, QHash<QString, IDocumentController *> controllers, LessonModel *model);
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
};

#endif // WHITEBOARD_H
