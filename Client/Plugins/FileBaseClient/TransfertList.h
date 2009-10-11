#ifndef TRANSFERTLIST_H
#define TRANSFERTLIST_H

#include <QWidget>
#include <QGridLayout>
class FileDataPlugin;
class FileTransfert;

class TransfertList : public QWidget
{
	Q_OBJECT
public:
					TransfertList();

private slots:
	void			refreshTransfert(int progress);
	void			append(FileTransfert*);
	void			remove(FileTransfert*);

private:
	QGridLayout*	layout;
};

#endif // TRANSFERTLIST_H
