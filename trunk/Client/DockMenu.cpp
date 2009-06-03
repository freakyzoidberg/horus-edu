#include "DockMenu.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>

#include "MainWindow.h"

DockMenu::DockMenu(QWidget *parent, PluginManager *pluginManager) : QDockWidget::QDockWidget(parent)
{
    this->pluginManager = pluginManager;
    IDisplayablePlugin *plugin = 0;
    QWidget *widget;
    QVBoxLayout *layout;
    QPushButton *item;

    this->ui.setupUi(this);
    widget = new QWidget();
    layout = new QVBoxLayout(widget);
    if (pluginManager)
        plugin = pluginManager->findDisplayablePlugin("MainFrame");
    if (plugin)
    {
        item = new QPushButton("Main Board");
        item->setObjectName("MainFrame");
        layout->addWidget(item);
        connect(item, SIGNAL(clicked()), this, SLOT(itemClicked()));
    }
    plugin = pluginManager->findDisplayablePlugin("Course");
    if (plugin)
    {
        item = new QPushButton("Course");
        item->setObjectName("Course");
        layout->addWidget(item);
        connect(item, SIGNAL(clicked()), this, SLOT(itemClicked()));
    }
    plugin = pluginManager->findDisplayablePlugin("Administration");
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
    IDisplayablePlugin *plugin;

    plugin = pluginManager->findDisplayablePlugin(QObject::sender()->objectName());
    ((MainWindow *) this->parent())->setCentralWidget(plugin->getWidget());
}
