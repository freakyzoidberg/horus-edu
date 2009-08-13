#ifndef __MANAGERTHREAD_H__
# define __MANAGERTHREAD_H__

# include <QThread>
# include <QMutex>
# include <QString>
# include <QEvent>

# include "AbstractManager.h"

class ManagerThread : public AbstractManager, public QThread
{
	Q_OBJECT

public:
	ManagerThread(QString managerName);
	~ManagerThread();
	bool event(QEvent *event);

protected:
	void run();
	QString	_managerName;
	AbstractManager *embedded;
	QMutex	init;

protected slots:
	void notify(QString message);
	void load(int percentage);
};

#endif
