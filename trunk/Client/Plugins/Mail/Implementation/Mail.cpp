#include		"Mail.h"
#include            "MailPanel.h"
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
