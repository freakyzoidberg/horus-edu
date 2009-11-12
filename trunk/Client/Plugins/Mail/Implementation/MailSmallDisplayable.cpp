#include		"MailSmallDisplayable.h"

#include		<QLabel>

const QString	MailSmallDisplayable::pluginName() const
{
	return ("MailSmallDisplayable");
}

const QString	MailSmallDisplayable::pluginVersion() const
{
	return ("0.1");
}

QWidget			*MailSmallDisplayable::getWidget()
{
	return (new QLabel(tr("Fill me with the last mails !")));
}

const QString	MailSmallDisplayable::getDisplayableName() const
{
	return (tr("Last mails"));
}

QIcon			MailSmallDisplayable::getIcon() const
{
	return (QIcon(":/mail.png"));
}
