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
#ifndef FILETRANSFERTCLIENT_H
#define FILETRANSFERTCLIENT_H

#include "../../../Common/DataImplementations/FileDataBase/FileTransfert.h"

class FileTransfertClient : public FileTransfert
{
  Q_OBJECT
public:
	FileTransfertClient(FileData* file, TransfertType type, const QByteArray& key);
	inline int			speed() const { return _speed; }
	inline int			isFinished() const { return _isFinished; }


private:
	void				connectToServer();

	bool				_isFinished;
	int					_speed;
	QTimer				_speedTimer;
	qint64				_lastProgress;
	uint				_startTime;

signals:
	void				speedChange(int);

private slots:
	void				connexionEncrypted();
	void				calcSpeed();
	void				finish();
};

class FileTransfertQueue : public QObject
{
	Q_OBJECT

public:
	static FileTransfertQueue*		instance() { static FileTransfertQueue* queue = new FileTransfertQueue;	return queue; }
	inline static const QList<FileTransfertClient*> list() { return instance()->_list; }
	
	inline void						append(FileTransfertClient* t) { _list.append(t); emit started(t); }
	inline void						remove(FileTransfertClient* t) { _list.removeOne(t); }
	inline void						clear() { _list.clear(); }

signals:
	void							started(FileTransfert*);

private:
									FileTransfertQueue() {}
									~FileTransfertQueue() {}
	QList<FileTransfertClient*>		_list;
};

#endif // FILETRANSFERTCLIENT_H
