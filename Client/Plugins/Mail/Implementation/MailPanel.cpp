#include	"MailPanel.h"


MailPanel::MailPanel(MailDataPlugin *MailPlugin): QTabWidget()
{
    ml = new MailList(MailPlugin,this);
    mf = new MailForm(MailPlugin);
        this->addTab(ml, QIcon(":/mail.png"), tr("MailBox"));
        this->addTab(mf, QIcon(":/write.png"), tr("Write Mail"));



}
