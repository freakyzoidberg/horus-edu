#include	"MailPanel.h"

#include	"MailList.h"
#include	"MailForm.h"

MailPanel::MailPanel(MailDataPlugin *MailPlugin): QTabWidget()
{
	this->addTab(new MailList(MailPlugin), QIcon(":/mail.png"), tr("MailBox"));
	this->addTab(new MailForm(MailPlugin), tr("Write Mail"));
}
