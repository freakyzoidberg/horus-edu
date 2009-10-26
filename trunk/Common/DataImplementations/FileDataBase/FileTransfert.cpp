#include "FileTransfert.h"

#include "FileDataBase.h"

FileTransfert::FileTransfert(FileData* file, TransfertType type)
{
	_fileData = (FileDataBase*)(file);
	_type = type;
	_socket = 0;
	_file = 0;
	_hash = 0;
	_progress = 0;

	FileTransfertList::list().append(this);
}

 void FileTransfert::socketToFile()
{
	if ( ! _socket->bytesAvailable())
		return;

	qint64 len = _socket->read(_buffer, TRANSFERT_BUFFER_SIZE);
	_file->write(_buffer, len);
	_progress += len;
	emit progressChange(_progress);

#ifdef HORUS_SERVER
	_hash->addData(_buffer, len);
#endif

	socketToFile();
}

void FileTransfert::fileToSocket(qint64)
{
	if (_file->atEnd())// || ! _socket->isWritable())
		_socket->close();

	qint64 len = _file->read(_buffer, TRANSFERT_BUFFER_SIZE);
	_socket->write(_buffer, len);
	_progress += len;
	emit progressChange(_progress);
	//	_socket->flush();

#ifdef HORUS_CLIENT
	_hash->addData(_buffer, len);
#endif
}
