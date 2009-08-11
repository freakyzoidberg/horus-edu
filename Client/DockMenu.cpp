#include "DockMenu.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>

#include "MainWindow.h"
#include "PluginManagerClient.h"
#include "DisplayablePlugin.h"

DockMenu::DockMenu(QWidget *parent) : QDockWidget(parent)
{
    DisplayablePlugin *plugin = 0;
    QWidget *widget;
    QVBoxLayout *layout;
    QPushButton *item;

    this->ui.setupUi(this);
    widget = new QWidget();
    layout = new QVBoxLayout(widget);
    plugin = PluginManagerClient::instance()->findPlugin<DisplayablePlugin*>("MainFrame");
    if (plugin)
    {
        item = new QPushButton("Main Board");
        item->setObjectName("MainFrame");
        layout->addWidget(item);
        connect(item, SIGNAL(clicked()), this, SLOT(itemClicked()));
    }
    plugin = PluginManagerClient::instance()->findPlugin<DisplayablePlugin*>("Course");
    if (plugin)
    {
        item = new QPushButton("Course");
        item->setObjectName("Course");
        layout->addWidget(item);
        connect(item, SIGNAL(clicked()), this, SLOT(itemClicked()));
    }
    plugin = PluginManagerClient::instance()->findPlugin<DisplayablePlugin*>("Administration");
    if (plugin)
    {
        item = new QPushButton("Administration");
        item->setObjectName("Administration");
        layout->addWidget(item);
        connect(item, SIGNAL(clicked()), this, SLOT(itemClicked()));
    }
    layout->addWidget(new QWidget, 1);
    widget->setLayout(layout);
    this->setWidget(widget);
}

void DockMenu::itemClicked()
{
    DisplayablePlugin *plugin;

    plugin = PluginManagerClient::instance()->findPlugin<DisplayablePlugin*>(sender()->objectName());
    ((MainWindow *)parent())->setCentralWidget(plugin->getWidget());
}
