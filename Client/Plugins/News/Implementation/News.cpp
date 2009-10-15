#include		"News.h"
#include "../../../../Common/PluginManager.h"
#include "newsplugin.h"
const QString	News::pluginName() const
{
	return ("News");
}

const QString	News::pluginVersion() const
{
	return ("0.1");
}

QWidget			*News::getWidget()
{
        return new NewsPlugin();
}

const QString       News::getDisplayableName() const
{
    return("News");
}

int           News::getOrder() const
{
    return (100);
}

bool                News::canLoad() const
{

                return (true);

}

void                News::load()
{
 //   MailPlugin = pluginManager->findPlugin<MailDataPlugin *>();
    Plugin::load();
}

QIcon News::getIcon() const
{
    //return (QIcon(":/mail.png"));
}
