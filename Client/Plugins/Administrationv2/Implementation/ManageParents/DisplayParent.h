#ifndef		__DISPLAYPARENT_H__
# define	__DISPLAYPARENT_H__

# include	<QWidget>

# include	"../../../../../Common/UserData.h"

class		DisplayParent : public QWidget
{
	Q_OBJECT

public:
	DisplayParent(QWidget *parent);
	DisplayParent(QWidget *parent, UserData *user);
};

#endif
