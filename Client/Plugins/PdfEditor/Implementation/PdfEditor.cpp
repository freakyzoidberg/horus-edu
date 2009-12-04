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
#include "PdfEditor.h"

#include <QDomDocument>
#include <QTreeWidgetItem>

#include "TreeWidgetItem.h"

const QString	PdfEditor::pluginName() const
{
	return ("PdfEditor");
}

const QString	PdfEditor::pluginVersion() const
{
	return ("0.1");
}

QWidget     *PdfEditor::getTocInWidget()
{
    //recuperer la toc d'une facon ou d'une autre, jsais pas encore trop comment
    //QDomDocument    toc = <machin_cast>dispPdf()->getToc();
    //QDomDocument *toc;


    QTreeWidget *tree = new QTreeWidget();
    //TreeWidgetItem *child = new TreeWidgetItem(tree, this);

    //buildTocWidget(toc, child);
    this->tree = tree;
    return tree;
}

void     PdfEditor::buildTocWidget(QDomNode *toc, TreeWidgetItem *parent)
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


