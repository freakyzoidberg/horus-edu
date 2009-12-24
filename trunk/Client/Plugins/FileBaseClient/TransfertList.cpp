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
#include "TransfertList.h"
#include "FileTransfertClient.h"
#include "../../../Common/FileData.h"
#include <QGridLayout>
#include <QLabel>
#include <QProgressBar>

QString calcUnit(qint64 nbrBytes)
{
	qreal nbr = nbrBytes;
	static QString units[] = {
		QObject::tr("b"),
		QObject::tr("kb"),
		QObject::tr("Mb"),
		QObject::tr("Gb"),
		QObject::tr("Tb")
	};
	int p = 0;
	while (nbr > 2000)
	{
		nbr /= 1024;
		p++;
	}

	return QVariant(((qreal)(qRound(nbr * 10))) / 10).toString() + units[p];
}


TransfertList::TransfertList()
{
	_grid = new QGridLayout(this);
	_grid->setColumnStretch(1, 1);

	foreach (FileTransfert* transfert, FileTransfertQueue::list())
		newTransfert(transfert);

	connect(FileTransfertQueue::instance(), SIGNAL(started(FileTransfert*)),  this, SLOT(newTransfert(FileTransfert*)));
}

void TransfertList::newTransfert(FileTransfert* transfert)
{
	new Transfert(transfert, this);
}

Transfert::Transfert(FileTransfert* transfert, TransfertList* list)
{
	_transfert = (FileTransfertClient*)(transfert);
	_list = list;
	int row = _list->_list.count();
	_list->_list.append(this);

	QProgressBar* bar = new QProgressBar;
	bar->setFixedHeight(14);
	if (_transfert->isFinished())
	{
		bar->setRange(0, 100);
		bar->setValue(100);
	}
	else
	{
		bar->setRange(0, _transfert->file()->size());
		bar->setValue(_transfert->progress());
	}

	_list->_grid->addWidget(new QLabel(_transfert->file()->name()), row, 0);
	_list->_grid->addWidget(bar, row, 1);
	_list->_grid->addWidget(new QLabel, row, 2);

	progressChange(0);

	connect(_transfert, SIGNAL(progressChange(int)), this, SLOT(progressChange(int)));
	connect(_transfert, SIGNAL(speedChange(int)), this, SLOT(progressChange(int)));
	connect(_transfert, SIGNAL(finished()), this, SLOT(finished()));
}

void Transfert::progressChange(int progress)
{
	int row = _list->_list.indexOf(this);
	static_cast<QProgressBar*>(_list->_grid->itemAtPosition(row, 1)->widget())->setValue(_transfert->progress());
	static_cast<QLabel*>(_list->_grid->itemAtPosition(row, 2)->widget())->setText((calcUnit(_transfert->progress()) + "/"
											  + calcUnit(_transfert->file()->size()) + " "
											  + calcUnit(_transfert->speed()) + "/s"));
}

void Transfert::finished()
{
	int row = _list->_list.indexOf(this);
	QProgressBar* bar = static_cast<QProgressBar*>(_list->_grid->itemAtPosition(row, 1)->widget());
	bar->setValue(_transfert->progress());
	bar->setRange(0, 100);
	bar->setValue(100);
}
