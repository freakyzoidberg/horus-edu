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
#include <QtCore/qplugin.h>
#include <QDebug>
#include <QtXml/QXmlSimpleReader>
#include <QFile>
#include <QFrame>

#include "../../../../Common/PluginManager.h"
#include "../../../../Common/FileDataPlugin.h"
#include "../../../../Common/FileData.h"

#include "LessonModel_ext.h"
#include "LessonManager.h"

bool	LessonManager::canLoad() const
{
	if (pluginManager->findPlugin<TreeDataPlugin*>() && pluginManager->findPlugin<FileDataPlugin*>())
        return (true);
    return (false);
}

void    LessonManager::load()
{
	//lessonModel = new LessonModel_ext(pluginManager);
	Plugin::load();
}

void    LessonManager::unload()
{
    delete lessonModel;
}

const QString	LessonManager::pluginName() const
{
	return ("LessonManager");
}

const QString	LessonManager::pluginVersion() const
{
	return ("1.1");
}

LessonModel* LessonManager::getLessonModel()
{
	if (lessonModel == NULL)
		lessonModel = new LessonModel_ext(pluginManager);
    return lessonModel;
}
