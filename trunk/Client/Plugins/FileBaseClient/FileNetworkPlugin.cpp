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
#include "../../../Common/DataImplementations/FileDataBase/FileDataBase.h"

void FileNetworkPlugin::receivePacket(const PluginPacket packet)
{
    if (packet.request != "downloadAuthorized" && packet.request != "uploadAuthorized")
        return;

    QVariantHash data = packet.data.toHash();
	FileDataBase* file = ((FileDataBase*)(_dataPlugin->file( data["file"].toUInt() )));

    if (packet.request == "downloadAuthorized")
		new FileTransfertClient(file, FileTransfert::DOWNLOAD, data["key"].toByteArray());
    else
		new FileTransfertClient(file, FileTransfert::UPLOAD,   data["key"].toByteArray());
}

void FileNetworkPlugin::askForTransfert(FileData* file, FileTransfert::TransfertType type)
{
	if (type == FileTransfert::DOWNLOAD)
		emit sendPacket(PluginPacket("File Network Plugin", "askForDownload", file->id()));
	else
		emit sendPacket(PluginPacket("File Network Plugin", "askForUpload", file->id()));
}
