#ifndef __NOTIFICATION_H__
# define __NOTIFICATION_H__

# include <QMetaType>

class Notification
{
public:
	enum type { DEBUG, MESSAGE, WARNING, ERROR, FATAL, YES_NO, LOGIN, RETRY };

};

Q_DECLARE_METATYPE(Notification::type)

#endif
