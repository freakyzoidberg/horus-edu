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
#ifndef FILEDATABASE_H
#define FILEDATABASE_H

#ifdef HORUS_SERVER
    #include <QtSql>
#endif
#ifdef HORUS_CLIENT
    #include <QVariant>
#endif
#include <QByteArray>
#include <QDateTime>
#include "../../Defines.h"
#include "../../FileData.h"
#include "FileDataBasePlugin.h"

class UserData;
class TreeData;
class FileNetworkPlugin;
class FileDataBase : public FileData
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerFileData)
  friend class FileTransfertServer;
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientFileData)
  friend class FileTransfertClient;
#endif

  friend class FileDataBasePlugin;

public:
    // INTERFACE Data
	void				keyToStream(QDataStream& s) const;
	void				dataToStream(QDataStream& s) const;
	void				dataFromStream(QDataStream& s);

	bool				canChange(UserData* user) const;
	bool				canAccess(UserData* user) const;

	const QList<Data*>	dependsOfCreatedData() const;

	QDebug				operator<<(QDebug debug) const;

#ifdef HORUS_CLIENT
	QVariant			data(int column, int role = Qt::DisplayRole) const;
#endif
#ifdef HORUS_SERVER
	quint8				serverRead();
	quint8				serverCreate();
	quint8				serverSave();
	quint8				serverRemove();
#endif


    // INTERFACE FileData
public:
	inline quint32		id() const { return _id; }

	inline QString		name() const { return _name; }
	void				setName(const QString name);

	inline UserData*	owner() const { return _owner; }

	inline TreeData*	node() const { return _node; }
	void				moveTo(TreeData* node);

	inline QString		mimeType() const { return _mimeType; }
	void				setMimeType(const QString name);

	inline QString		keyWords() const { return _keyWords; }
	void				setKeyWords(const QString keyWords);

	inline QByteArray	hash() const { return _hash; }
	inline quint64		size() const { return _size; }

	QString				fileName() const;

private:
    FileDataBase(quint32 fileId, FileDataBasePlugin* plugin);
	quint32				_id;
	QString				_name;
	QString				_mimeType;
	QString				_keyWords;
	quint64				_size;
	TreeData*			_node;
	UserData*			_owner;
	QByteArray			_hash;

#ifdef HORUS_CLIENT
public:
	//! return true if the file is downloaded in local
	bool				isDownloaded() const;
public slots:
	//! upload the file to the server.
	void				upload(const QString localFileName);
	//! download the file from the server.
	void				download();

private slots:
	void				upload();

private:
	bool				_isDownloaded;
#endif
};

#endif // FILEDATABASE_H
