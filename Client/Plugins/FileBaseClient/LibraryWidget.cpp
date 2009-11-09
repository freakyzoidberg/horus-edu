#include "LibraryWidget.h"

#include "LibraryModel.h"

#include <QComboBox>
#include <QListView>

LibraryWidget::LibraryWidget(PluginManager* pluginManager)
{
	_layout = new QHBoxLayout(this);

	QComboBox* combo = new QComboBox(this);
	combo->addItem("Filter 1");
	_layout->addWidget(combo);

	QListView* list = new QListView(this);
	list->setModel(new LibraryModel(pluginManager));
	_layout->addWidget(list);
}
