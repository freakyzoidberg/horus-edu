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
