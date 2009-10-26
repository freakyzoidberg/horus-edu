#ifndef __ABSTRACTMANAGER_H__
# define __ABSTRACTMANAGER_H__

# include <QObject>
# include <QString>

# include "Notification.h"

class AbstractManager : virtual public QObject
{
	Q_OBJECT

signals:
	void notified(Notification::type, QString message);
	void loaded(int percentage);
};

#endif
