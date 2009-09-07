#include "DockMenu.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>

#include "MainWindow.h"
#include "MetaManager.h"
#include "PluginManagerClient.h"
#include "DisplayablePlugin.h"

DockMenu::DockMenu(QWidget *parent) : QDockWidget(parent)
{
    QWidget *widget;
    QVBoxLayout *layout;

    this->ui.setupUi(this);
    widget = new QWidget();
    layout = new QVBoxLayout(widget);
    foreach (DisplayablePlugin* plugin ,MetaManager::getInstance()->findManager<PluginManager *>()->findPlugins<DisplayablePlugin*>())
    {
        QString title = plugin->getDisplayableName();
        if ( ! title.isEmpty())
        {
            QPushButton *item = new QPushButton(title);
            item->setObjectName(plugin->pluginName());
            layout->addWidget(item);
            connect(item, SIGNAL(clicked()), this, SLOT(itemClicked()));
        }
    }
    layout->addWidget(new QWidget, 1);
    widget->setLayout(layout);
    this->setWidget(widget);
}

void DockMenu::itemClicked()
{
    DisplayablePlugin *plugin;

    plugin = MetaManager::getInstance()->findManager<PluginManager *>()->findPlugin<DisplayablePlugin*>(sender()->objectName());
    ((MainWindow *)parent())->setCentralWidget(plugin->getWidget());
}
