#ifndef __ABSTRACTMANAGER_H__
# define __ABSTRACTMANAGER_H__

# include <QObject>
# include <QString>

class AbstractManager : virtual public QObject
{
	Q_OBJECT

public:
	virtual ~AbstractManager() {}

signals:
	void notified(QString message);
	void loaded(int percentage);

};

#endif