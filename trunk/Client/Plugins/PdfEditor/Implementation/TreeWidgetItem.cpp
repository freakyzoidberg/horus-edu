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
#include "TreeWidgetItem.h"

TreeWidgetItem::TreeWidgetItem(QTreeWidget * tree, QObject * parent)
                            : QTreeWidgetItem(tree)
        
{
    this->parent = parent;\
}

TreeWidgetItem::TreeWidgetItem(TreeWidgetItem * child, QObject * parent)
                            : QTreeWidgetItem(child)
{
    this->parent = parent;
}

TreeWidgetItem::~TreeWidgetItem()
{

}

int TreeWidgetItem::getPageBegin()
{
    return this->pageBegin;
}

int TreeWidgetItem::getPageEnd()
{
    return this->pageEnd;
}

double  TreeWidgetItem::getPosXBegin()
{
    return this->posXBegin;
}

double  TreeWidgetItem::getPosXEnd()
{
    return this->posYBegin;
}

double  TreeWidgetItem::getPosYEnd()
{
    return this->posYEnd;
}


void TreeWidgetItem::setPageBegin(int page)
{
    pageBegin = page;
}

void TreeWidgetItem::setPageEnd(int page)
{
    pageEnd = page;
}

void  TreeWidgetItem::setPosXBegin(double pos)
{
    posXBegin = pos;
}

void  TreeWidgetItem::setPosXEnd(double pos)
{
    posYBegin = pos;
}

void  TreeWidgetItem::setPosYEnd(double pos)
{
    posYEnd = pos;
}
