#include "DockMenu.h"
#include "DockMenuItem.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QtAlgorithms>

#include "MainWindow.h"
#include "MetaManager.h"
#include "PluginManagerClient.h"

DockMenu::DockMenu(MainWindow* parent) : QDockWidget(parent)
{
    QWidget* widget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(widget);

    ui.setupUi(this);

	QList<DisplayablePlugin *> plugins;

	plugins = MetaManager::getInstance()->findManager<PluginManager *>()->findPlugins<DisplayablePlugin*>();
	qSort(plugins.begin(), plugins.end(), DockMenu::lessThan);
    foreach (DisplayablePlugin* plugin, plugins)
    {
        QString title = plugin->getDisplayableName();
        if ( ! title.isEmpty())
        {
            DockMenuItem* item = new DockMenuItem(plugin, plugin->getDisplayableName(), plugin->getIcon());
			item->setStyleSheet("QPushButton{text-align: left;}");
            layout->addWidget(item);
            connect(item, SIGNAL(clicked()), this, SLOT(itemClicked()));
        }
    }
    layout->addWidget(new QWidget, 1);
    widget->setLayout(layout);
    setWidget(widget);
}

void DockMenu::itemClicked()
{
    QWidget* widget = ((DockMenuItem*)sender())->getPluginWidget();
    ((MainWindow*)parent())->setCentralWidget(widget);
}

bool	DockMenu::lessThan(DisplayablePlugin *a, DisplayablePlugin *b)
{
	return (a->getOrder() < b->getOrder());
}
