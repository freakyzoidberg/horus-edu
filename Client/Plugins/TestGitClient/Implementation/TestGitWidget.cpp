#include "TestGitWidget.h"
#include "TestGit.h"

#include "../../../../Common/PluginManager.h"

#include "../../../../Common/UserDataPlugin.h"
#include "../../../../Common/UserData.h"

#include "../../../../Common/SettingsDataPlugin.h"
#include "../../../../Common/SettingsData.h"

#include "../../../../Common/TreeDataPlugin.h"
#include "../../../../Common/TreeData.h"

#include "../../../../Common/FileDataPlugin.h"
#include "../../../../Common/FileData.h"

#include "TestNetworkPlugin.h"

#include <QPushButton>
#include <QDebug>
#include <QDateTime>
#include <QTreeView>

TestGitWidget::TestGitWidget(TestGit* _plugin, TestNetworkPlugin* testNetworkPlugin)
{
    plugin = _plugin;

    QPushButton* bt0 = new QPushButton("test 0 download file");
    connect(bt0, SIGNAL(clicked()), this, SLOT(test0()));
    layout.addWidget(bt0, 0, 0);
    layout.setRowStretch(0, 0);

    QPushButton* bt1 = new QPushButton("test 1 send Network plugin");
    connect(bt1, SIGNAL(clicked()), testNetworkPlugin, SLOT(sendTest()));
    layout.addWidget(bt1, 1, 0);
    layout.setRowStretch(1, 1);

    QPushButton* bt2 = new QPushButton("test 2 upload file");
    connect(bt2, SIGNAL(clicked()), this, SLOT(test2()));
    layout.addWidget(bt2, 2, 0);
    layout.setRowStretch(2, 2);

    QPushButton* bt3 = new QPushButton("test 3 ...");
    connect(bt3, SIGNAL(clicked()), this, SLOT(test3()));
    layout.addWidget(bt3, 3, 0);
    layout.setRowStretch(3, 3);

    TreeDataPlugin* tree = plugin->pluginManager->findPlugin<TreeDataPlugin*>();
    if (tree)
    {
        QTreeView *tv = new QTreeView();
        tv->setModel(tree->getTreeModel());
        layout.setRowStretch(4, 0);
        layout.addWidget(tv, 4, 0);
        //tv->expandAll();
    }

    setLayout(&layout);
}

void TestGitWidget::test0()
{
    FileDataPlugin* p = plugin->pluginManager->findPlugin<FileDataPlugin*>();
    if ( ! p)
        return;

    FileData* f = p->getFile(1);
    if ( ! f)
        return;

    f->download();
}

void TestGitWidget::test1()
{
}

void TestGitWidget::test2()
{
    FileDataPlugin* p = plugin->pluginManager->findPlugin<FileDataPlugin*>();
    if ( ! p)
        return;

    FileData* f = p->getFile(1);
    if ( ! f)
        return;

    QFile* file = f->file();
    file->open(QIODevice::WriteOnly | QIODevice::Truncate);
    file->write("alors esque ca va mercher???");
    file->close();
    delete file;

    f->upload();
}

void TestGitWidget::test3()
{
}
