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

    MainLayout->addWidget(new QLabel(tr("Class :")),0,0,Qt::AlignLeft);

    if (pluginManager->currentUser()->level() == LEVEL_STUDENT)
    {
    MainLayout->addWidget(new QLabel(pluginManager->currentUser()->studentClass()->name()),0,1,Qt::AlignLeft);
    _sceneWidget = new EdtSceneProxyWidget(_pluginManager, pluginManager->currentUser()->studentClass(),760,560);
    _sceneWidget->setMinimumSize(760,580);
    MainLayout->addWidget(_sceneWidget,1,0,1,2,Qt::AlignLeft);
    }
        else
    {
    _sceneWidget = NULL;
    }
    this->setMaximumSize(760,560);
    this->setLayout(MainLayout);
}


void EdtWidget::createScene(TreeData *td)
{
    //MainLayout->addWidget(new QLabel(tr("Class :")),0,0,Qt::AlignLeft);
    //MainLayout->removeItem(MainLayout->itemAtPosition(0,1));
    if (_currentClass)
        delete _currentClass;
    _currentClass = new QLabel(td->name());
    MainLayout->addWidget(_currentClass,0,1,Qt::AlignLeft);

    qDebug() << __FILE__ <<":" << __LINE__ << "slot:createScene() called";
    if (_sceneWidget)
        delete _sceneWidget;
    _sceneWidget = new EdtSceneProxyWidget(_pluginManager, td,750,550);
    _sceneWidget->setMinimumSize(760,580);
      this->setMaximumSize(760,560);
    MainLayout->addWidget(_sceneWidget,1,0,1,2,Qt::AlignLeft);
}
