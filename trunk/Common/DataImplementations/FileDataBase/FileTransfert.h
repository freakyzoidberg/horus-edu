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
#ifndef FILETRANSFERT_H
#define FILETRANSFERT_H

#include <QHash>
#include <QByteArray>
#include <QSslSocket>
#include <QTimer>
#include <QFile>
#include <QMutex>
#include <QCryptographicHash>
class FileData;
class FileDataBase;
#define TRANSFERT_BUFFER_SIZE 32768

//! the object for each file transfert
class FileTransfert : public QObject
{
  Q_OBJECT

public:
	enum TransfertType { DOWNLOAD, UPLOAD };
	inline FileData*	file() const { return _fileData; }
	inline const QByteArray& key() const { return _key; }
	inline TransfertType type() const { return _type; }
	//! return the progress value (for a down/up-load)
	inline int			progress() const { return _progress; }

protected:
	FileTransfert(FileData* file, TransfertType type);

	//! the associated FileData*
	FileData*			_fileData;
	//! type : DOWNLOAD / UPLOAD
	TransfertType       _type;
	//! transfert socket
    QSslSocket*         _socket;
	//! local file
	QFile				_file;
	//! to calculate the hash in live
	QCryptographicHash* _hash;
	//! transfert buffer
	char				_buffer[TRANSFERT_BUFFER_SIZE];
	//! the key to authenticate the new connexion
	QByteArray          _key;
	qint64				_progress;

signals:
	void progressChange(int);
	void finished();

protected slots:
    void socketToFile();
    void fileToSocket(qint64);
};

#endif // FILETRANSFERT_H
