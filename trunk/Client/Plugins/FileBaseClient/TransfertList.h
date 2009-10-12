#ifndef TRANSFERTLIST_H
#define TRANSFERTLIST_H

#include <QWidget>
#include <QGridLayout>
class FileDataPlugin;
class FileTransfert;

class Transfert : public QHBoxLayout
{
	Q_OBJECT
public:
					Transfert(FileTransfert*);

private slots:
	void			refresh(int progress);
	void			finished();

private:
	FileTransfert*	_transfert;
};

class TransfertList : public QWidget
{
	Q_OBJECT
public:
					TransfertList();

private slots:
	void			newTransfert(FileTransfert*);
};

#endif // TRANSFERTLIST_H
