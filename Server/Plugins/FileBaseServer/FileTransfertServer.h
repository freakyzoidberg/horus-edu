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
#ifndef FILETRANSFERTSERVER_H
#define FILETRANSFERTSERVER_H

#include "../../../Common/DataImplementations/FileDataBase/FileTransfert.h"

class UserData;
class FileNetworkPlugin;
class FileTransfertServer : public FileTransfert
{
  Q_OBJECT
public:
	FileTransfertServer(FileData* file, UserData* user, TransfertType type, FileNetworkPlugin* plugin);
	~FileTransfertServer();
	inline UserData*					user() const { return _user; }

private:
	QTimer*								_timer;
	UserData*							_user;
	FileNetworkPlugin*					_networkPlugin;

private slots:
	void								init();
private:
	void								start(QSslSocket* socket);
	void								checkQueue();


	//STATIC: QUEUE MANAGEMENT
public:
	static void							registerSocket(const QByteArray& key, QSslSocket* socket);

private:
	static QList<FileTransfertServer*>	_transferts;
	static QList<FileTransfertServer*>	_queue;
	static QByteArray					generateUniqueKey();
};

#endif // FILETRANSFERTSERVER_H
