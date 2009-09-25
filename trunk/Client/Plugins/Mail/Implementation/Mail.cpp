#include		"Mail.h"
#include            "MailPanel.h"
#include <QIcon>
const QString	Mail::pluginName() const
{
	return ("Mail");
}

const QString	Mail::pluginVersion() const
{
	return ("0.1");
}

QWidget			*Mail::getWidget()
{
        return new MailPanel();
}

const QString       Mail::getDisplayableName() const
{
    return("Mailbox");
}

const int           Mail::getOrder() const
{
    return (100);
}

bool                Mail::canLoad() const
{
    return true;
}

void                Mail::load()
{
    Plugin::load();
}

QIcon Mail::getIcon() const
{
    return (QIcon(":/mail.png"));
}
