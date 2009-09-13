#include "MainFrameWidget.h"

#include "../../../Common/PluginManager.h"
#include "../../../Common/TreeDataPlugin.h"

#include "../../../Common/FileDataPlugin.h"
#include "../../../Common/FileData.h"
#include "../../../Common/File.h"


#include <QPushButton>
#include <QDebug>
#include <QDateTime>
#include <QTreeView>

MainFrameWidget::MainFrameWidget(MainFrame *_plugin) : QFrame()
{
    this->layout = new QGridLayout;
    Plugin *course = 0;
    QPushButton *button;

    this->plugin = _plugin;
    ui.setupUi(this);

    TreeDataPlugin* tree = plugin->pluginManager->findPlugin<TreeDataPlugin*>();
    if (tree)
    {
        QTreeView *tv = new QTreeView();
        tv->setModel(tree->getTreeModel());
        layout->setRowStretch(2, 0);
        layout->addWidget(tv, 2, 0);
        tv->expandAll();
    }

    course = plugin->pluginManager->findPlugin<DisplayablePlugin*>("Course");
    if (course)
    {
        button = new QPushButton("My Lessons");
        layout->addWidget(button, 2, 0);
        layout->setRowStretch(2, 0);
        connect(button, SIGNAL(clicked()), plugin, SLOT(courseClicked()));
    }
    layout->setRowStretch(0, 0);
    layout->setRowStretch(1, 1);
    this->setLayout(layout);

    connectedAs = new QLabel("Not connected", this);
    this->layout->addWidget(connectedAs, 0, 0);
    lastLogin = new QLabel("Last login: Never", this);
    this->layout->addWidget(lastLogin, 0, 1);
    updateInfos();
}

#include "../../../Common/SettingsData.h"

void    MainFrameWidget::updateInfos()
{
    qDebug() << "MainFrameWidget::updateInfos";

    UserData* user = plugin->pluginManager->currentUser();

    if ( ! user)
        return;

    connect(user, SIGNAL(updated()), this, SLOT(updateInfos()));

    connectedAs->setText("Connected as: " + user->login() + " (" + user->name() + " " + user->surname() + ")");

    if (user->lastLogin().isValid())
        lastLogin->setText("Last login: " + user->lastLogin().toString());
    else
        lastLogin->setText("Last login: Never");
}
