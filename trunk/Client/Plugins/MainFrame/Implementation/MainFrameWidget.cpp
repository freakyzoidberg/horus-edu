#include "MainFrameWidget.h"

#include "../../../Common/PluginManager.h"
#include "../../../Common/TreeDataPlugin.h"

#include "../../../Common/FileDataPlugin.h"
#include "../../../Common/FileData.h"

#include "../../../Common/UserData.h"

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

    //TreeDataPlugin* tree = plugin->pluginManager->findPlugin<TreeDataPlugin*>();
    //if (tree)
    //{
    //    QTreeView *tv = new QTreeView();
    //    tv->setModel(tree->getWhiteBoardModel());
    //    layout->setRowStretch(2, 0);
    //    layout->addWidget(tv, 2, 0);

    //    tv->expandAll();
    //}

    course = plugin->pluginManager->findPlugin<DisplayablePlugin*>("Course");
    if (course)
    {
        button = new QPushButton(QIcon(":/Pictures/edit.png"), tr("My Lessons"));
        layout->addWidget(button, 2, 0);
        layout->setRowStretch(2, 0);
        connect(button, SIGNAL(clicked()), plugin, SLOT(courseClicked()));
    }
    layout->setRowStretch(0, 0);
    layout->setRowStretch(1, 1);
	//FAKE
        button = new QPushButton(QIcon(":/Pictures/calendarwidget.png"), tr("My Calendar"));
        layout->addWidget(button, 2, 1);
        button = new QPushButton(QIcon(":/Pictures/book.png"), tr("My Marks"));
        layout->addWidget(button, 3, 0);
        button = new QPushButton(QIcon(":/Pictures/history.png"), tr("My Projects"));
        layout->addWidget(button, 3, 1);
        layout->setRowStretch(3, 0);
	//FIN FAKE
    this->setLayout(layout);

    connectedAs = new QLabel(tr("Not connected"), this);
    this->layout->addWidget(connectedAs, 0, 0);
    lastLogin = new QLabel(tr("Last login: Never"), this);
    this->layout->addWidget(lastLogin, 0, 1);
    updateInfos();
}

#include "../../../Common/SettingsData.h"

void    MainFrameWidget::updateInfos()
{
    UserData* user = plugin->pluginManager->currentUser();

    if ( ! user)
        return;

    connect(user, SIGNAL(updated()), this, SLOT(updateInfos()));

    connectedAs->setText(tr("Connected as: ") + user->login() + tr(" (") + user->name() + tr(" ") + user->surname() + tr(")"));

    if (user->lastLogin().isValid())
        lastLogin->setText(tr("Last login: ") + user->lastLogin().toString());
    else
        lastLogin->setText(tr("Last login: Never"));
}
