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
