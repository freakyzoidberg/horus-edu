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
    MainLayout = new QHBoxLayout();
    MainLayout->setSpacing(0);
    MainLayout->setMargin(2);

    if (pluginManager->currentUser()->level() == LEVEL_STUDENT)
    {
    _sceneWidget = new EdtSceneProxyWidget(_pluginManager, pluginManager->currentUser()->studentClass());    
    MainLayout->addWidget(_sceneWidget);
    }
        else
    {
    _sceneWidget = NULL;
    }
    this->setLayout(MainLayout);
}


void EdtWidget::createScene(TreeData *td)
{
    qDebug() << __FILE__ <<":" << __LINE__ << "slot:createScene() called";
    if (_sceneWidget)
        delete _sceneWidget;
    _sceneWidget = new EdtSceneProxyWidget(_pluginManager, td);
    MainLayout->addWidget(_sceneWidget);
}
