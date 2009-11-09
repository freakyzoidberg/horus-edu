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
