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
#include "MainFrame.h"

#include "../../Common/PluginManager.h"
#include "../../Common/TreeDataPlugin.h"
#include "../../Common/SettingsDataPlugin.h"
#include "MainFrameWidget.h"

bool MainFrame::canLoad() const
{
        if (pluginManager->findPlugin<TreeDataPlugin*>() && pluginManager->findPlugin<SettingsDataPlugin*>())
		return (true);
	return (false);
}

void MainFrame::load()
{
    TreeDataPlugin* t = pluginManager->findPlugin<TreeDataPlugin*>();
    if (!t->isLoaded())
        t->load();
    Plugin::load();
}

QWidget* MainFrame::getWidget()
{
    return (new MainFrameWidget(pluginManager));
}

void MainFrame::courseClicked()
{
    emit switchToWidget(pluginManager->findPlugin<DisplayablePlugin*>("Course")->getWidget());
}

int	MainFrame::getOrder() const
{
	return (-1);
}

QIcon		MainFrame::getIcon() const
{
	return (QIcon(":/Pictures/icon"));
}
