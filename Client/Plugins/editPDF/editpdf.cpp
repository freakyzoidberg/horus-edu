#include "editpdf.h"

#include <QDomDocument>

EditPDF::EditPDF()
{
   this->pluginsRequired.append("dispPDF");
}

QWidget     *EditPDF::getTocInWidget(QDomNode * toc , QTreeWidgetItem * parent)
{
    //recuperer la toc d'une facon ou d'une autre, jsais pas encore trop comment
    //QDomDocument    toc = <machin_cast>dispPdf()->getToc();

    QDomNode n = brToc->firstChild();

    while (!n.isNull())
    {
       QDomElement e = n.toElement();
       QTreeWidgetItem *child = new QTreeWidgetItem(parent);

       child->setText(0, e.tagName());

       if (e.hasChildNodes())
       {
           nbSp++;
           browseToc(&n, child);
           nbSp--;
       }
       n = n.nextSibling();
       i++;
    }
}
