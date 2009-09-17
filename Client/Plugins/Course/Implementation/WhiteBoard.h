#ifndef WHITEBOARD_H
#define WHITEBOARD_H

#include <QWidget>
#include <QDragEnterEvent>
#include <QPushButton>
#include <QToolBar>
#include <QHash>
#include <QVector>
#include <QToolBox>

#include "../../LessonManager/IDocumentController.h"
#include "../../../../Common/FileDataPlugin.h"
#include "WhiteBoardData.h"

class Items;

class WhiteBoard : public QWidget
{
public:
     WhiteBoard(FileDataPlugin *filePlugin, QHash<QString, IDocumentController *> controllers);
     void   setTmp(Items *);
     Items  *getTmp();
     void   setPosInDoc(int posInDoc);
     int    getPosInDoc();
     QToolBar *dock;
     QVector<QPushButton *>   button;

protected:
     void dragEnterEvent(QDragEnterEvent *event);
     void dragMoveEvent(QDragMoveEvent *event);
     void dropEvent(QDropEvent *event);
     QHash<QString, IDocumentController *> _controllers;

 private:
     Items   *tmp;
     int    posInDoc;
     WhiteBoardData wbdata;
};

#endif // WHITEBOARD_H
