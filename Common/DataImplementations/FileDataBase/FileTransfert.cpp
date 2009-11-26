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
