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
#include "FileNetworkPlugin.h"
#include "FileTransfertServer.h"
#include "../../../Common/FileData.h"
#include "../../../Common/PluginManager.h"
#include "../../../Common/DataImplementations/FileDataBase/FileDataBasePlugin.h"

void FileNetworkPlugin::receivePacket(UserData* user, const PluginPacket packet)
{
    if (packet.request != "askForDownload" && packet.request != "askForUpload")
        return;

	FileData* file = _dataPlugin->pluginManager->findPlugin<FileDataBasePlugin*>()->file( packet.data.toUInt() );
	if ( ! file)
		return;

	if (packet.request == "askForDownload")
		new FileTransfertServer(file, user, FileTransfert::DOWNLOAD, this);
	else
		new FileTransfertServer(file, user, FileTransfert::UPLOAD, this);

}

void FileNetworkPlugin::transfertCanStart(FileTransfertServer* transfert)
{
	QVariantHash data;
	data["file"] = transfert->file()->id();
	data["key"] = transfert->key();

	if (transfert->type() == FileTransfert::DOWNLOAD)
		emit sendPacket(transfert->user(), PluginPacket("File Network Plugin", "downloadAuthorized", data));
	else
		emit sendPacket(transfert->user(), PluginPacket("File Network Plugin", "uploadAuthorized"  , data));
}
