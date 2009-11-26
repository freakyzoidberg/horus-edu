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
#include <QTreeView>
#include <QGridLayout>

#include "CreateWhiteboardDialog.h"
#include "WhiteBoardModel.h"

CreateWhiteboardDialog::CreateWhiteboardDialog(PluginManager *pluginManager) : _node(NULL)
{
	setWindowTitle(tr("Start a new class"));
	QGridLayout* dlgLayout = new QGridLayout(this);

	QTreeView* treeView = new QTreeView();
        _model = new WhiteBoardModel(pluginManager);
        _proxyModel = new QSortFilterProxyModel(this);
        _proxyModel->setFilterRegExp(QRegExp("\\b(ROOT|CLASSES|GRADE|SUBJECT|WHITEBOARD)\\b", Qt::CaseSensitive, QRegExp::RegExp));
        _proxyModel->setFilterKeyColumn(1);
        _proxyModel->setSourceModel(_model);
        treeView->setModel(_proxyModel);
	treeView->setAnimated(true);
	treeView->setAutoExpandDelay(100);
	treeView->setRootIsDecorated(false);
	treeView->setHeaderHidden(true);
	treeView->expandAll();
	treeView->setSelectionMode(QAbstractItemView::SingleSelection);
	QObject::connect(treeView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(selectionChanged(QModelIndex,QModelIndex)));

	dlgLayout->addWidget(treeView, 0, 0, 1, 2);
        _cancel = new QPushButton(tr("Cancel"));
        _start = new QPushButton(tr("Start here"));
        _start->setEnabled(false);
        QObject::connect(_cancel, SIGNAL(pressed()), this, SLOT(cancel()));
        QObject::connect(_start, SIGNAL(pressed()), this, SLOT(startHere()));
        dlgLayout->addWidget(_cancel, 1, 0);
        dlgLayout->addWidget(_start, 1, 1);
}

void	CreateWhiteboardDialog::startHere()
{
        if (_node)
            done(QDialog::Accepted);
        else
            done(QDialog::Rejected);
}

void	CreateWhiteboardDialog::cancel()
{
        done(QDialog::Rejected);
}

void	CreateWhiteboardDialog::selectionChanged(QModelIndex current, QModelIndex previous)
{
    _node = NULL;
    _start->setEnabled(false);
    if (current.isValid() && current.internalPointer() != NULL)
    {
        TreeData *tdata = qobject_cast<TreeData*>(static_cast<QObject*>(_proxyModel->mapToSource(current).internalPointer()));
        if (tdata && tdata->type() == "SUBJECT")
        {
            _node = tdata;
            _start->setEnabled(true);
        }
    }
}
