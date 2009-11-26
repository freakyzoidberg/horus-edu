/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "TestGitWidget.h"
#include "TestGit.h"

#include "../../../Common/PluginManager.h"

#include "../../../Common/UserDataPlugin.h"
#include "../../../Common/UserData.h"

#include "../../../Common/SettingsDataPlugin.h"
#include "../../../Common/SettingsData.h"

#include "../../../Common/TreeDataPlugin.h"
#include "../../../Common/TreeData.h"

#include "../../../Common/FileDataPlugin.h"
#include "../../../Common/FileData.h"
#include "../../../Common/File.h"

#include "TestNetworkPlugin.h"

#include <QPushButton>
#include <QDebug>
#include <QDateTime>
#include <QTreeView>

TestGitWidget::TestGitWidget(TestGit* _plugin, TestNetworkPlugin* testNetworkPlugin)
{
    plugin = _plugin;

    QPushButton* bt0 = new QPushButton("test 0 File");
    connect(bt0, SIGNAL(clicked()), this, SLOT(test0()));
    layout.addWidget(bt0, 0, 0);
    layout.setRowStretch(0, 0);

    QPushButton* bt1 = new QPushButton("test 1 send Network plugin");
    connect(bt1, SIGNAL(clicked()), testNetworkPlugin, SLOT(sendTest()));
    layout.addWidget(bt1, 1, 0);
    layout.setRowStretch(1, 1);

    QPushButton* bt2 = new QPushButton("test 2 ...");
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
        tv->expandAll();
    }

    setLayout(&layout);
}

void TestGitWidget::test0()
{
    qDebug() << "test0.0";
    FileDataPlugin* p = plugin->pluginManager->findPlugin<FileDataPlugin*>();
    if ( ! p)
        return;

    qDebug() << "test0.1";
    FileData* f = p->getFile(1);
    if ( ! f)
        return;

    f->update();
    qDebug() << "test0.2";
}

void TestGitWidget::test1()
{
}

void TestGitWidget::test2()
{
}

void TestGitWidget::test3()
{
}
