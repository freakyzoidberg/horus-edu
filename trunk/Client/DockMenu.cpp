#include "DockMenu.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>

DockMenu::DockMenu(QWidget *parent, PluginManager *pluginManager) : QDockWidget::QDockWidget(parent)
{
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
        layout->addWidget(item);
    }
    plugin = pluginManager->findDisplayablePlugin("Course");
    if (plugin)
    {
        item = new QPushButton("Course");
        layout->addWidget(item);
    }
    plugin = pluginManager->findDisplayablePlugin("Administration");
    if (plugin)
    {
        item = new QPushButton("Administration");
        layout->addWidget(item);
    }
    layout->addWidget(new QWidget, 1);
    widget->setLayout(layout);
    this->setWidget(widget);
}
