#include "TransfertList.h"
#include "FileTransfertClient.h"
#include "../../../Common/FileData.h"
#include <QGridLayout>
#include <QLabel>
#include <QProgressBar>

TransfertList::TransfertList()
{
	layout = new QGridLayout(this);

	foreach (FileTransfert* transfert, (QList<FileTransfert*>&)FileTransfertList::list())
		append(transfert);

	connect(&FileTransfertList::list(), SIGNAL(started(FileTransfert*)),  this, SLOT(append(FileTransfert*)), Qt::DirectConnection);
	connect(&FileTransfertList::list(), SIGNAL(finished(FileTransfert*)), this, SLOT(remove(FileTransfert*)), Qt::DirectConnection);
}

void TransfertList::append(FileTransfert* transfert)
{
	int row = FileTransfertList::list().size();

	QProgressBar* bar = new QProgressBar;
	bar->setRange(0, transfert->file()->size());
	bar->setValue(transfert->progress());
	bar->setFixedHeight(16);

	layout->addWidget(new QLabel(QVariant(row).toString()), row, 0);
	layout->addWidget(new QLabel(QVariant(transfert->file()->id()).toString()), row, 1);
	layout->addWidget(new QLabel(transfert->file()->name()), row, 2);
	layout->addWidget(bar, row, 3);
	layout->addWidget(new QLabel(QVariant(transfert->progress()).toString()), row, 4);
	layout->addWidget(new QLabel("/" + QVariant(transfert->file()->size()).toString()), row, 5);

	layout->setRowStretch(row,     0);
	layout->setRowStretch(row + 1, 1);

	connect(transfert, SIGNAL(progressChange(int)), this, SLOT(refreshTransfert(int)));
}

void TransfertList::remove(FileTransfert* transfert)
{
	disconnect(transfert, SIGNAL(progressChange(int)), this, SLOT(refreshTransfert(int)));

	int row = FileTransfertList::list().indexOf(transfert);

	qDebug() << "remove" << row;

	layout->removeWidget(layout->itemAtPosition(row, 0)->widget());
	layout->removeWidget(layout->itemAtPosition(row, 1)->widget());
	layout->removeWidget(layout->itemAtPosition(row, 2)->widget());
	layout->removeWidget(layout->itemAtPosition(row, 3)->widget());
	layout->removeWidget(layout->itemAtPosition(row, 4)->widget());
	layout->removeWidget(layout->itemAtPosition(row, 5)->widget());

	layout->update();
}

void TransfertList::refreshTransfert(int progress)
{
	int row = FileTransfertList::list().indexOf((FileTransfert*)sender());
	QLayoutItem* item;

	if ((item = layout->itemAtPosition(row, 3)))
		((QProgressBar*)(item->widget()))->setValue(progress);

	if ((item = layout->itemAtPosition(row, 4)))
		((QLabel*)(item->widget()))->setText(QVariant(progress).toString());
}
