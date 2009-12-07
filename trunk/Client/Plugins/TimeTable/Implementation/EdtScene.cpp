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

#define SCENE_WIDTH 700
#include <QGraphicsRectItem>
#include <QGraphicsItemGroup>
#include <QGraphicsTextItem>
#define VOFFSET 40
#define HOFFSET 50
#define CWIDTH 100

EDTScene::EDTScene(PluginManager *pluginManager, TreeData *treedata) : _pluginManager(pluginManager)
{

    qDebug() << __FILE__ <<":" << __LINE__ << "EDTScene constructor called for node " << treedata->id();
    _SD = pluginManager->findPlugin<ScheduleDataPlugin*>()->schedule(treedata);
    if (_SD != NULL)
    {
    qDebug() << __FILE__ <<":" << __LINE__ << "EDTScene from " << _SD->startDate() << " to " << _SD->endDate();
    qDebug() << __FILE__ <<":" << __LINE__ << "EDTScene with " << _SD->scheduleEvents().count() << " Events";

    for (int i = 0; i < _SD->scheduleEvents().size(); ++i) {

    addEvent(_SD->scheduleEvents().at(i)->getName(),_SD->scheduleEvents().at(i)->getJWeek(), _SD->scheduleEvents().at(i)->getHStart(),_SD->scheduleEvents().at(i)->getHEnd(),QColor(Qt::red));
    }

    //(getWPosforDay(1), 1 * VOFFSET,CWIDTH,100,QPen(), QBrush(QColor(Qt::red)))

   // this->addRect(0,0,100,100,QPen(), QBrush(QColor(Qt::white)));



    //this->addRect(getWPosforDay(1), 1 * VOFFSET,CWIDTH,100,QPen(), QBrush(QColor(Qt::red)));
    //this->addRect(getWPosforDay(2), 1 * VOFFSET + 100,CWIDTH,200,QPen(), QBrush(QColor(Qt::red)));
    //this->addRect(getWPosforDay(3), 1 * VOFFSET + 100,CWIDTH,200,QPen(), QBrush(QColor(Qt::red)));
    //this->addRect(getWPosforDay(4), 1 * VOFFSET + 100,CWIDTH,200,QPen(), QBrush(QColor(Qt::red)));
    //this->addRect(getWPosforDay(5), 1 * VOFFSET + 100,CWIDTH,200,QPen(), QBrush(QColor(Qt::red)));

    }
    else
        qDebug() << __FILE__ <<":" << __LINE__ << "EDTScene _SD == NULL";

}

int                 EDTScene::getWPosforDay(int day)
{
    if ((day > 0) && (day <= 7))
    {

    return(day * HOFFSET + ((day - 1) * HOFFSET) + 1);
    }

    return 0;
}


void                EDTScene::addEvent(QString name, int dow, QTime hstart, QTime hend, QColor color)
{

    int offset = -1 * QTime(7,0,0,0).secsTo(QTime(0,0,0,0));
    int start = -1 * hstart.secsTo(QTime(0,0,0,0));

    int total = ((start - offset) / 60) * 0.667;
    int duration = (hstart.secsTo(hend) / 60) * 0.667;


    QGraphicsItemGroup *group = new QGraphicsItemGroup(0,this);
    QGraphicsRectItem *rect = new QGraphicsRectItem(0,0,CWIDTH,duration);
    QGraphicsTextItem *text = new QGraphicsTextItem(name);
    QGraphicsTextItem *time = new QGraphicsTextItem(hstart.toString("hh:mm") + " " + hend.toString("hh:mm"));

    rect->setGroup(group);
    rect->setZValue(1);
    rect->setBrush(QBrush(color));
    text->setParentItem(group);
    text->setTextWidth(100);
    text->setFont(QFont("arial",8,1,false));
    text->setZValue(100);
    time->setPos(5,10);
    time->setParentItem(group);
    time->setTextWidth(100);
    time->setZValue(101);
    //text->setPos(5,10);
    group->setToolTip(name + " @ "+ hstart.toString("hh:mm") + " to " + hend.toString("hh:mm"));












    group->setPos(getWPosforDay(1), dow * VOFFSET + total);
}
