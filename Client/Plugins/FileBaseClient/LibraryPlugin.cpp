#include "LibraryPlugin.h"
#include "LibraryList.h"
#include "LibraryEdit.h"
#include <QStackedLayout>


QWidget* LibraryPlugin::getWidget()
{
	QWidget* widget = new QWidget;
	QStackedLayout* layout = new QStackedLayout(widget);
	layout->addWidget(new LibraryList(pluginManager, layout));
	return widget;
}
