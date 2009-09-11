#include "DockMenu.h"
#include "DockMenuItem.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>

#include "MainWindow.h"
#include "MetaManager.h"
#include "PluginManagerClient.h"
#include "DisplayablePlugin.h"

DockMenu::DockMenu(MainWindow* parent) : QDockWidget(parent)
{
    QWidget* widget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(widget);

    ui.setupUi(this);

    foreach (DisplayablePlugin* plugin ,MetaManager::getInstance()->findManager<PluginManager *>()->findPlugins<DisplayablePlugin*>())
    {
        QString title = plugin->getDisplayableName();
        if ( ! title.isEmpty())
        {
            DockMenuItem* item = new DockMenuItem(plugin, title);
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
