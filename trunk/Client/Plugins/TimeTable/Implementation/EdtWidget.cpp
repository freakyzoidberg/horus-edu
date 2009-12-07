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
#include "EdtWidget.h"

# include <QDebug>
EdtWidget::EdtWidget(PluginManager *pluginManager) : _pluginManager(pluginManager)
{
    _currentClass = 0;
    MainLayout = new QGridLayout();
    MainLayout->setSpacing(0);
    MainLayout->setMargin(2);
    scrollArea = new QScrollArea();

    if (pluginManager->currentUser()->level() == LEVEL_STUDENT)
    {
    _sceneWidget = new EdtSceneProxyWidget(_pluginManager, pluginManager->currentUser()->studentClass(),760,560);
    _sceneWidget->setMinimumSize(760,580);
    _sceneWidget->setMaximumSize(760,580);
    _sceneWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollArea->setWidget(_sceneWidget);
    scrollArea->setMaximumSize(765,585);
    MainLayout->addWidget(scrollArea,0,0,Qt::AlignLeft);
    }
    else if (pluginManager->currentUser()->level() <= LEVEL_ADMINISTRATOR)
    {

        QVBoxLayout *RightLayout = new QVBoxLayout();
        RightLayout->setSpacing(2);

        QLabel *infoTitle = new QLabel(tr("Informations:"));
        infoTitle->setProperty("isTitle", true);
        infoTitle->setProperty("isRound", true);
        informationsFrame = new QFrame(this);
        informationsFrame->setMinimumWidth(200);


        QVBoxLayout *informationsLayout = new QVBoxLayout(informationsFrame);
        informationsLayout->setSpacing(0);
        informationsLayout->setMargin(0);
        informationsLayout->addWidget(infoTitle);
        RightLayout->addWidget(informationsFrame);

        QLabel *actionTitle = new QLabel(tr("Actions:"));
        actionTitle->setProperty("isTitle", true);
        actionTitle->setProperty("isRound", true);

        //_del = new QPushButton(QIcon(":/DelTimeTable.png"), tr("Delete this edt"));
        //_edit = new QPushButton(QIcon(":/EditTimeTable.png"), tr("Edit this edt"));
        _ok = new QPushButton(QIcon(":/ok.png"), tr("Ok"));
        _save = new QPushButton(QIcon(":/save.png"), tr("Apply"));
        _reset = new QPushButton(QIcon(":/reset.png"), tr("Reset"));
        _back = new QPushButton(QIcon(":/back.png"), tr("Cancel"));
        _add = new QPushButton(QIcon(":/AddTimeTable.png"), tr("Add"));

        RightLayout->addWidget(actionTitle);
        //RightLayout->addWidget(edit);
        //RightLayout->addWidget(del);
        RightLayout->addWidget(_ok);
        RightLayout->addWidget(_save);
        RightLayout->addWidget(_reset);
        RightLayout->addWidget(_back);
        RightLayout->addWidget(_add);
        RightLayout->addWidget(new QWidget(this), 1);

        MainLayout->addLayout(RightLayout,0,1);

    }
        else
    {
    _sceneWidget = NULL;
    }

    this->setLayout(MainLayout);
}


void EdtWidget::createScene(TreeData *td)
{


    if (_sceneWidget)
        delete _sceneWidget;
    _sceneWidget = new EdtSceneProxyWidget(_pluginManager, td,760,560);
    _sceneWidget->setMinimumSize(760,580);
    _sceneWidget->setMaximumSize(760,580);

    scrollArea->setWidget(_sceneWidget);
    scrollArea->setMaximumSize(765,585);
    MainLayout->addWidget(scrollArea,0,0);
}
