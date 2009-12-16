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
	(new QVBoxLayout(this))->addStretch(1);

	foreach (FileTransfert* transfert, FileTransfertQueue::list())
		newTransfert(transfert);

	connect(FileTransfertQueue::instance(), SIGNAL(started(FileTransfert*)),  this, SLOT(newTransfert(FileTransfert*)));
}

void TransfertList::newTransfert(FileTransfert* transfert)
{
	((QVBoxLayout*)layout())->insertLayout(0, new Transfert(transfert));
}

Transfert::Transfert(FileTransfert* transfert)
{
	_transfert = (FileTransfertClient*)(transfert);

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

	addWidget(new QLabel(_transfert->file()->name()), 10); //0
	addWidget(bar, 50); //1
	addWidget(new QLabel, 10); //2

	progressChange(0);

	connect(_transfert, SIGNAL(progressChange(int)), this, SLOT(progressChange(int)));
	connect(_transfert, SIGNAL(speedChange(int)), this, SLOT(progressChange(int)));
	connect(_transfert, SIGNAL(finished()), this, SLOT(finished()));
}

void Transfert::progressChange(int progress)
{
	static_cast<QProgressBar*>(itemAt(2)->widget())->setValue(_transfert->progress());
	static_cast<QLabel*>(itemAt(2)->widget())->setText((calcUnit(_transfert->progress()) + "/"
											  + calcUnit(_transfert->file()->size()) + " "
											  + calcUnit(_transfert->speed()) + "/s"));
}

void Transfert::finished()
{
	QProgressBar* bar = ((QProgressBar*)(itemAt(2)->widget()));
	bar->setRange(0, 100);
	bar->setValue(100);
}
