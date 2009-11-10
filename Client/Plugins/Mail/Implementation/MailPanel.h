#ifndef				MAILPANEL_H
# define			MAILPANEL_H

# include			<QTabWidget>

# include			"../../../../Common/DataImplementations/MailData/MailDataPlugin.h"

class				MailPanel : public QTabWidget
{
    Q_OBJECT

public:
    MailPanel(MailDataPlugin *MailPlugin);
};

#endif //			MAILPANEL_H
