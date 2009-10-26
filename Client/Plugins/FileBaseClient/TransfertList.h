#ifndef TRANSFERTLIST_H
#define TRANSFERTLIST_H

#include <QWidget>
#include <QGridLayout>
class FileDataPlugin;
class FileTransfert;
class FileTransfertClient;

class Transfert : public QHBoxLayout
{
	Q_OBJECT
public:
					Transfert(FileTransfert*);

private slots:
	void			progressChange(int progress);
	void			speedChange(int speed);
	void			finished();

private:
	FileTransfertClient*	_transfert;
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
