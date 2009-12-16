#include "LibraryPlugin.h"
#include "LibraryList.h"
#include "LibraryEdit.h"
#include <QStackedLayout>


QWidget* LibraryPlugin::getWidget()
{
	QWidget* widget = new QWidget;
	_layout = new QStackedLayout(widget);

	LibraryList* list = new LibraryList(pluginManager);
	_layout->addWidget(list);
	connect(list, SIGNAL(editFile(FileData*)), this, SLOT(editFile(FileData*)));

	return widget;
}

void LibraryPlugin::editFile(FileData* file)
{
	delete _layout->takeAt(0);
	LibraryEdit* edit = new LibraryEdit(pluginManager, file);
	_layout->addWidget(edit);
	connect(edit, SIGNAL(exited()), this, SLOT(editFinished()));
}

void LibraryPlugin::editFinished()
{
	delete _layout->takeAt(0);
	LibraryList* list = new LibraryList(pluginManager);
	_layout->addWidget(list);
	connect(list, SIGNAL(editFile(FileData*)), this, SLOT(editFile(FileData*)));
}
