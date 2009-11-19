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
