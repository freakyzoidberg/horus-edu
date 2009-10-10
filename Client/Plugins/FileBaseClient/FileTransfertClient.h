#ifndef FILETRANSFERTCLIENT_H
#define FILETRANSFERTCLIENT_H

#include "../../../Common/DataImplementations/FileDataBase/FileTransfert.h"

class FileTransfertClient : public FileTransfert
{
  Q_OBJECT
public:
	FileTransfertClient(FileData* file, TransfertType type, const QByteArray& key);
	QWidget* progressBar();

private:
	void				connectToServer();

private slots:
	void				connexionEncrypted();
};

#endif // FILETRANSFERTCLIENT_H
