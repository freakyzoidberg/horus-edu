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
#include "EdtScene.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#define SCENE_WIDTH 700
EDTScene::EDTScene()
{


    addFullDayBGtoScene(-(SCENE_WIDTH / 2) + 0 * (SCENE_WIDTH / 8),(SCENE_WIDTH / 8));
    addFullDayBGtoScene(-(SCENE_WIDTH / 2) + 1 * (SCENE_WIDTH / 8),(SCENE_WIDTH / 8));
    addFullDayBGtoScene(-(SCENE_WIDTH / 2) + 2 * (SCENE_WIDTH / 8),(SCENE_WIDTH / 8));
    addFullDayBGtoScene(-(SCENE_WIDTH / 2) + 3 * (SCENE_WIDTH / 8),(SCENE_WIDTH / 8));
    addFullDayBGtoScene(-(SCENE_WIDTH / 2) + 4 * (SCENE_WIDTH / 8),(SCENE_WIDTH / 8));
    addFullDayBGtoScene(-(SCENE_WIDTH / 2) + 5 * (SCENE_WIDTH / 8),(SCENE_WIDTH / 8));
    addFullDayBGtoScene(-(SCENE_WIDTH / 2) + 6 * (SCENE_WIDTH / 8),(SCENE_WIDTH / 8));
    addFullDayBGtoScene(-(SCENE_WIDTH / 2) + 7 * (SCENE_WIDTH / 8),(SCENE_WIDTH / 8));
}


void EDTScene::addFullDayBGtoScene(int pos,int wid)
{
    for (int i = 0; i < 13; i++)
    {
        QGraphicsRectItem *rect = new QGraphicsRectItem(pos, i * 20, wid, 20, 0, this);
        //this->addRect(pos, i * 20, wid, 20, QPen(), QBrush(QColor(Qt::white)));
    }
}


void EDTScene::mousePressEvent(QGraphicsSceneMouseEvent* e)
{
    qDebug() << "clicked < ";
    if (this->items(e->scenePos().toPoint()).count() > 0)
    {
        qDebug() << e->scenePos().rx();// << ((QGraphicsRectItem*)this->items(e->scenePos().toPoint()).first())->pos().ry();
        //QGraphicsRectItem *rect = new QGraphicsRectItem(
        QGraphicsSimpleTextItem *text = new QGraphicsSimpleTextItem("Math", ((QGraphicsRectItem*)this->itemAt(e->scenePos().toPoint())));
        text->setPos(-320, 40);
        //((QGraphicsRectItem*)this->items(e->scenePos().toPoint()).first())->setBrush(QBrush(QColor(Qt::red)));
    }
}
