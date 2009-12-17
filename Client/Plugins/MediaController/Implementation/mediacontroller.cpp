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

#include "mediacontroller.h"
#include "player.h"
#include "../../../../Common/PluginManager.h"
#include "../../../../Common/FileData.h"
#include "../../../../Common/FileDataPlugin.h"

MediaController::MediaController()
{
}

MediaController::~MediaController()
{

}

const QString   MediaController::pluginName() const
{
    return "MediaController";
}

const QString   MediaController::pluginVersion() const
{
    return "0.2";
}

const QString   MediaController::getSupportedType() const
{
    return ("Media");
}

QWidget*        MediaController::createDocumentWidget(ILessonDocument *document, QWidget *loadicon)
{
    int fileId = document->getParameters().value("name").toInt();
	FileData *data = pluginManager->findPlugin<FileDataPlugin*>()->file(fileId);
    Player *player = new Player(data, loadicon);
    return player;
}

QWidget    *MediaController::editDocument(QFile *, ILessonDocument *)
{
	return (0);
}

QIcon		MediaController::getIcon()
{
	return QIcon(":/video-icon.png");
}
