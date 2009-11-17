#ifndef		__DISPLAYTEACHER_H__
# define	__DISPLAYTEACHER_H__

# include	<QWidget>

# include	"../../../../../Common/UserData.h"

class		DisplayTeacher : public QWidget
{
	Q_OBJECT

public:
	DisplayTeacher(QWidget *parent);
	DisplayTeacher(QWidget *parent, UserData *user);
};

#endif
