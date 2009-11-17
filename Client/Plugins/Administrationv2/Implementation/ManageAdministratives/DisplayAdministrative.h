#ifndef		__DISPLAYADMINISTRATIVE_H__
# define	__DISPLAYADMINISTRATIVE_H__

# include	<QWidget>

# include	"../../../../../Common/UserData.h"

class		DisplayAdministrative : public QWidget
{
	Q_OBJECT

public:
	DisplayAdministrative(QWidget *parent);
	DisplayAdministrative(QWidget *parent, UserData *user);
};

#endif
