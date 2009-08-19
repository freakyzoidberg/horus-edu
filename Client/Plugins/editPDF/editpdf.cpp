#include "editpdf.h"

#include <QDomDocument>
#include <QTreeWidgetItem>

#include "TreeWidgetItem.h"

EditPDF::EditPDF()
{
   this->pluginsRequired.append("dispPDF");
}

QWidget     *EditPDF::getTocInWidget()
{
    //recuperer la toc d'une facon ou d'une autre, jsais pas encore trop comment
    //QDomDocument    toc = <machin_cast>dispPdf()->getToc();
    QDomDocument *toc;


    QTreeWidget *tree = new QTreeWidget();
    TreeWidgetItem *child = new TreeWidgetItem(tree, this);

    buildTocWidget(toc, child);
    this->tree = tree;
    return tree;
}

void     EditPDF::buildTocWidget(QDomNode *toc, TreeWidgetItem *parent)
{
    QDomNode n = toc->firstChild();

    while (!n.isNull())
    {
       QDomElement e = n.toElement();
       TreeWidgetItem *child = new TreeWidgetItem(parent, this);

       child->setText(0, e.tagName());

       if (e.hasChildNodes())
           buildTocWidget(&n, child);
       n = n.nextSibling();
    }
}


