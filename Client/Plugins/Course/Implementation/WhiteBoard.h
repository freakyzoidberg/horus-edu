#ifndef WHITEBOARD_H
#define WHITEBOARD_H

#include <QWidget>
#include <QDragEnterEvent>
#include <QToolBar>
#include <QHash>

#include "../../LessonManager/IDocumentController.h"

class Items;

class WhiteBoard : public QWidget
{
public:
     WhiteBoard(QHash<QString, IDocumentController *> controllers);
     void   setTmp(Items *);
     Items  *getTmp();
     void   setPosInDoc(int posInDoc);
     int    getPosInDoc();

     QToolBar *dock;

protected:
     void dragEnterEvent(QDragEnterEvent *event);
     void dragMoveEvent(QDragMoveEvent *event);
     void dropEvent(QDropEvent *event);
     QHash<QString, IDocumentController *> _controllers;

 private:
     Items   *tmp;
     int    posInDoc;
};

#endif // WHITEBOARD_H
