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
#include "EdtSceneProxyWidget.h"
#include <QGraphicsItem>

EdtSceneProxyWidget::EdtSceneProxyWidget(PluginManager *pluginManager, TreeData *treedata, qint8 width, qint8 height) : _pluginManager(pluginManager)
{

    _scene = new EDTScene(pluginManager, treedata);

    _scene->setBackgroundBrush(QPixmap(":/background.png"));
    _scene->setSceneRect(0,0, width,height);

    this->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    for (int i = 1; i <= 7; i++)
        !this->reDesignEvent(i);
    this->setScene(_scene);

}

EdtSceneProxyWidget::EdtSceneProxyWidget(PluginManager *pluginManager, qint8 width, qint8 height) : _pluginManager(pluginManager)
{

    _scene = new EDTScene(pluginManager);

    _scene->setBackgroundBrush(QPixmap(":/background.png"));
    _scene->setSceneRect(0,0, width,height);

    this->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    for (int i = 1; i <= 7; i++)
        this->reDesignEvent(i);
    this->setScene(_scene);

}

EdtSceneProxyWidget::~EdtSceneProxyWidget()
{
    if (_scene)
        delete _scene;
}



bool EdtSceneProxyWidget::reDesignEvent(int day)
{

   this->repaint();;
    QList<QGraphicsItem *> listItem =     _scene->items(QRectF(_scene->getWPosforDay(day),50,10,800) );


    QList<QGraphicsItemGroup*> listGroup;
    bool add;
    for (int i = 0; i < listItem.size(); i++)
    {
        if (listItem.at(i)->group() != 0)
        {
        add = true;
        for (int j = 0; j < listGroup.size(); j++)
            if (listGroup.at(j) == listItem.at(i)->group())
                add = false;
        if (add)
            listGroup.append(listItem.at(i)->group());
        }
    }


    for (int i = 0; i < listGroup.size(); i++)
    {
       if ((i < (listGroup.size() - 1)) && (listGroup.at(i)->collidingItems().size() < listGroup.at(i+1)->collidingItems().size()))
        {
           listGroup.swap(i,i+1);
           i = 0;
        }
    }

    if (listGroup.size() <= 0)
     return true;

    qDebug() << "There is " << listGroup.size() << " group Item";

    for (int j = 0; j < listGroup.size(); j++)
    {
    listGroup = getCollidingItemGroup(listGroup.at(j));

    if (listGroup.size() > 1)
    {


    int decalage;
    qDebug() << "Il ya " << listGroup.size() << " Collisions";

    decalage = (100)/ listGroup.size();

    for (int i = 0; i < listGroup.size(); i++)
        {
        listGroup.at(i)->setPos(listGroup.at(i)->x() + (i * decalage) - 2, listGroup.at(i)->y());
        listGroup.at(i)->scale(1/(static_cast<qreal>(listGroup.size()) + 0.15),1);
        }
    }
    }
 return false;

    /*
    QList<QGraphicsItem *> collisionlistItem = group->collidingItems();

    QList<QGraphicsItemGroup*> collisionlistGroup;
    bool add;
    for (int i = 0; i < collisionlistItem.size(); i++)
    {
        if (collisionlistItem.at(i)->group() != 0)
        {
        add = true;
        for (int j = 0; j < collisionlistGroup.size(); j++)
            if (collisionlistGroup.at(j) == collisionlistItem.at(i)->group())
                add = false;
        if (add)
            collisionlistGroup.append(collisionlistItem.at(i)->group());
        }
    }

    int decalage;
    if (collisionlistGroup.size() > 1)
    {
    decalage = (CWIDTH)/ collisionlistGroup.size();
    for (int i = 0; i < collisionlistGroup.size(); i++)
        {
        collisionlistGroup.at(i)->setPos(collisionlistGroup.at(i)->x() + (i * decalage),collisionlistGroup.at(i)->y());
        collisionlistGroup.at(i)->scale(1/static_cast<qreal>(collisionlistGroup.size()),1);

        }

    }
*/

}


QList<QGraphicsItemGroup*> EdtSceneProxyWidget::getCollidingItemGroup(QGraphicsItemGroup *group)
{
    QList<QGraphicsItem *> collisionlistItem = group->collidingItems(Qt::IntersectsItemBoundingRect);

    QList<QGraphicsItemGroup*> collisionlistGroup;
    bool add;
    for (int i = 0; i < collisionlistItem.size(); i++)
    {
        if (collisionlistItem.at(i)->group() != 0)
        {
        add = true;
        for (int j = 0; j < collisionlistGroup.size(); j++)
            if (collisionlistGroup.at(j) == collisionlistItem.at(i)->group())
                add = false;
        if (add)
        {
         //   if (collisionlistItem.at(i)->group() != group)
            collisionlistGroup.append(collisionlistItem.at(i)->group());
        }
        }
    }
    return collisionlistGroup;
}


int EdtSceneProxyWidget::getMaxColafterRedesign(QList<QGraphicsItemGroup*> listg)
{
    if (listg.size() <= 0)
        return 1;

    return 1;
}
