#ifndef				MAILPANEL_H
# define			MAILPANEL_H

# include			<QTabWidget>

# include			"../../../../Common/DataImplementations/MailData/MailDataPlugin.h"
#include	"MailList.h"
#include	"MailForm.h"
class MailList;
class MailForm;
class				MailPanel : public QTabWidget
{
    Q_OBJECT

public:
    MailPanel(MailDataPlugin *MailPlugin);
    MailForm* getForm() {return mf;}
private:
    MailList *ml;
    MailForm *mf;
};

#endif //			MAILPANEL_H
