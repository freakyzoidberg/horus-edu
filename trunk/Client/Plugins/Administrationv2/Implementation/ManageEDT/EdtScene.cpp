#include "EdtScene.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#define SCENE_WIDTH 800
EDTScene::EDTScene()
{


    addFullDayBGtoScene(-(SCENE_WIDTH / 2) + 0 * (SCENE_WIDTH / 7),(SCENE_WIDTH / 7));
    addFullDayBGtoScene(-(SCENE_WIDTH / 2) + 1 * (SCENE_WIDTH / 7),(SCENE_WIDTH / 7));
    addFullDayBGtoScene(-(SCENE_WIDTH / 2) + 2 * (SCENE_WIDTH / 7),(SCENE_WIDTH / 7));
    addFullDayBGtoScene(-(SCENE_WIDTH / 2) + 3 * (SCENE_WIDTH / 7),(SCENE_WIDTH / 7));
    addFullDayBGtoScene(-(SCENE_WIDTH / 2) + 4 * (SCENE_WIDTH / 7),(SCENE_WIDTH / 7));
    addFullDayBGtoScene(-(SCENE_WIDTH / 2) + 5 * (SCENE_WIDTH / 7),(SCENE_WIDTH / 7));
    //this->addRect(-(SCENE_WIDTH / 2) + (SCENE_WIDTH / 7),0,(SCENE_WIDTH / 7),10,QPen(), QBrush(QColor(Qt::white)));
    //this->addRect(-(SCENE_WIDTH / 2) + 2 * (SCENE_WIDTH / 7),0,(SCENE_WIDTH / 7),10,QPen(), QBrush(QColor(Qt::white)));

}


void EDTScene::addFullDayBGtoScene(int pos,int wid)
{
    for (int i = 0; i < 48; i++)
        this->addRect(pos, i * 10, wid, 10, QPen(), QBrush(QColor(Qt::white)));
}


void EDTScene::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
qDebug() << "clicked < ";
if (this->items(e->scenePos().toPoint()).count() > 0)
((QGraphicsRectItem*)this->items(e->scenePos().toPoint()).first())->setBrush(QBrush(QColor(Qt::red)));
}
