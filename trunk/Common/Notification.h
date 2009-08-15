#ifndef __NOTIFICATION_H__
# define __NOTIFICATION_H__

# include <QMetaType>

class Notification
{
public:
	enum type { UNDEFINED, ERROR, WARNING, MESSAGE, YES_NO, LOGIN, RETRY, __LAST__ };

};

Q_DECLARE_METATYPE(Notification::type)

#endif
