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
	while (nbr > 9000)
	{
		nbr /= 1024;
		p++;
	}

	return QVariant(qRound(nbr)).toString() + units[p];
}


TransfertList::TransfertList()
{
	(new QVBoxLayout(this))->addStretch(1);

	foreach (FileTransfert* transfert, (QList<FileTransfert*>&)FileTransfertList::list())
		newTransfert(transfert);

	connect(&FileTransfertList::list(), SIGNAL(started(FileTransfert*)),  this, SLOT(newTransfert(FileTransfert*)));
}

void TransfertList::newTransfert(FileTransfert* transfert)
{
	((QVBoxLayout*)layout())->insertLayout(0, new Transfert(transfert));
}

Transfert::Transfert(FileTransfert* transfert)
{
	_transfert = transfert;

	QProgressBar* bar = new QProgressBar;
	bar->setRange(0, transfert->file()->size());
	bar->setValue(transfert->progress());
	bar->setFixedHeight(14);

	addWidget(new QLabel(QVariant(transfert->file()->id()).toString())); //0
	addWidget(new QLabel(transfert->file()->name())); //1
	addWidget(bar, 1); //2
	addWidget(new QLabel(calcUnit(transfert->progress()))); //3
	addWidget(new QLabel("/" + calcUnit(transfert->file()->size()))); //4

	connect(transfert, SIGNAL(progressChange(int)), this, SLOT(refresh(int)));
	connect(transfert, SIGNAL(finished()), this, SLOT(finished()));
}

void Transfert::refresh(int progress)
{
	QProgressBar* bar = ((QProgressBar*)(itemAt(2)->widget()));
	bar->setValue(progress);

	((QLabel*)(itemAt(3)->widget()))->setText(calcUnit(progress));
}

void Transfert::finished()
{
	QProgressBar* bar = ((QProgressBar*)(itemAt(2)->widget()));
	bar->setRange(0, 100);
	bar->setValue(100);

//	((QLabel*)      (((QHBoxLayout*)layout())->itemAt(3)->widget()))->setText(QVariant(progress).toString());
}
