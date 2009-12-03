#ifndef				__MAILSMALLWIDGET_H__
# define			__MAILSMALLWIDGET_H__

# include			<QWidget>

# include			"../../../../Common/DataImplementations/MailData/MailDataPlugin.h"

class				MailSmallWidget : public QWidget
{
	Q_OBJECT

public:
	MailSmallWidget(MailDataPlugin *mailPlugin);

private:
	MailDataPlugin	*_mailPlugin;
};

#endif
