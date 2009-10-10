#include "TransfertList.h"
#include "FileTransfertClient.h"
#include <QBoxLayout>

TransfertList::TransfertList()
{
	QBoxLayout* layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
	foreach (FileTransfert* transfert, FileTransfert::transferts())
		layout->addWidget(((FileTransfertClient*)transfert)->progressBar());
	setLayout(layout);
}
