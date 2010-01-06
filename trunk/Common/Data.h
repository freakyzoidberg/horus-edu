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
#ifndef DATA_H
#define DATA_H

#include <QMutex>
#include <QMutexLocker>
#include <QDataStream>
#include <QString>
#include <QDebug>
#include <QVariant>
#include <QDateTime>
#ifdef HORUS_CLIENT
#  include <QColor>
#  include <QIcon>
#  include <QMimeData>
#endif

#include "DataPlugin.h"
#include "DataManager.h"
#include "PluginManager.h"
class UserData;

#define IS_VALID_DATA_STATUS(s) ((s != Data::EMPTY && s != Data::REMOVED && s != Data::REMOVING))

class Data : public QObject
{
	Q_OBJECT
#ifdef HORUS_CLIENT
	friend class DataManagerClient;
	friend class UserCache;
#endif
#ifdef HORUS_SERVER
	friend class DataManagerServer;
#endif

public:
	// Data streamed between Client and Server:    V->value     N->new key     E->error
	//                      //   Client|Server|Client |Server
	//                      //     to  |  to  |-Memory|-Memory
	//                      //   Server|Client|-Cache |
	enum Status { EMPTY,    // 0       |      |   X   |  X
				  CACHED,   // 1       |      |   X   |
				  UPTODATE, // 2       |      |   X   |  X

				  SAVING,   // 3  X  V |      |   X   |
				  CREATING, // 4  X  V |      |   X   |
				  REMOVING, // 5  X    |      |   X   |

				  UPDATED,  // 6       | X  V |       |
				  SAVED,    // 7       | X    |       |
				  CREATED,  // 8       | X  N |       |
				  REMOVED,  // 9       | X    |       |  X

				  DATA_ERROR,//10      | X EV |       |
				  __LAST_STATUS__};

	enum Error { NONE,
				 PERMITION_DENIED,
				 NOT_FOUND,
				 DATABASE_ERROR,
				 DATA_ALREADY_CHANGED,
				 INTERNAL_SERVER_ERROR,
				 __LAST_ERROR__ };

    //! Have to write his key into the stream to be able to identify this data with the server and the cache.
	virtual void			keyToStream(QDataStream& s) const = 0;
    //! Have to write his data into the stream.
    /*! Called to:
     *  - Transfert this data between client and server.
     *  - Write to a local cache file.
     *  - Compare two data.
     */
	virtual void			dataToStream(QDataStream& s) const = 0;
    //! Have to read his data from the stream.
    /*! Called to:
     *  - Transfert this data between client and server.
     *  - Read from a local cache file.
     */
	virtual void			dataFromStream(QDataStream& s) = 0;

    //! Return the current status of this data.
	inline quint8			status() const { return (quint8)_status; }
	inline const QDateTime	lastChange() const { return _lastChange; }

#ifdef HORUS_CLIENT
	inline bool				canAccess() { return canAccess(_plugin->pluginManager->currentUser()); }
	inline bool				canChange() { return canChange(_plugin->pluginManager->currentUser()); }
#endif
	virtual inline bool		canAccess(UserData*) const { return true; }
	virtual inline bool		canChange(UserData*) const { return true; }

	//! The data need that other dependants data being created to be saved or created.
	virtual inline const QList<Data*> dependsOfCreatedData() const { return QList<Data*>(); }

	inline const QString    dataType() const { return _plugin->dataType(); }

public slots:
	//! Function to create the value of the data
	inline void				create() { setStatus(CREATING); }
	//! Function to save the value of the data
	inline void				save() { setStatus(SAVING); }
	//! Function to delete the value of the data
	inline void				remove() { setStatus(REMOVING); }

signals:
	//! Signal emmited when the data is updated.
	void		            updated();
	//! Signal emmited when the data is removed.
	void                    removed();
	//! Signal emmited each time the status is changed.
	void					statusChanged();
	//! Signal emmited when an error occur on this data.
	void                    error(quint8 error);

public:
    //! Usefull for debuging. Not mandatory but important.
	virtual inline QDebug   operator<<(QDebug debug) const { return debug << dataType(); }
#ifdef HORUS_CLIENT
	enum Role { FILTER_ROLE=Qt::UserRole+1, SORT_ROLE=Qt::UserRole+2 };
	virtual inline QVariant		data(int, int = Qt::DisplayRole) const { return QVariant(); }
	virtual inline const QIcon	icon() const { static QIcon icon; return icon; }
	virtual inline bool			dropData(const QList<Data*>, Qt::DropAction) { return false; }
	inline void			send() { _plugin->dataManager->sendData(this); }
#endif
#ifdef HORUS_SERVER
    //! Create this data into the database, and update the key.
	virtual quint8		serverCreate() = 0;
    //! Save the current data into the database.
	virtual quint8		serverSave() = 0;
    //! Delete the current data from the database.
	virtual quint8		serverRemove() = 0;
	//! send this data to a user
	inline void			sendToUser(UserData* user) { _plugin->dataManager->sendData(user, this); }
#endif

protected:
	inline Data(DataPlugin* plugin) : mutex(QMutex::Recursive) { _plugin=plugin; _status=EMPTY; }
	inline ~Data() {}

    DataPlugin*             _plugin;
    quint8                  _status;
    QDateTime               _lastChange;

public:
	QMutex                  mutex;
private:
	//! Change the current status and tell the coresponding plugin the data just changed.
	inline void             setStatus(quint8 status) {
#ifdef HORUS_CLIENT
		QMetaObject::invokeMethod(_plugin->dataManager, "dataStatusChange", Qt::QueuedConnection, Q_ARG(Data*, this), Q_ARG(quint8, status));
#endif
#ifdef HORUS_SERVER
		_plugin->dataManager->dataStatusChange(this, status);
#endif
	}
};

inline QDebug operator<<(QDebug debug, const Data& data) { return data << debug; }
inline QDebug operator<<(QDebug debug, const Data* data) { if (data) return (*data) << debug; else return debug << "null"; }
inline QDebug operator<<(QDebug debug, Data::Status status) {
	const char* txtStatus[] = {
		"EMPTY",
		"CACHED",
		"UPTODATE",
		"SAVING",
		"CREATING",
		"REMOVING",
		"UPDATED",
		"SAVED",
		"CREATED",
		"REMOVED",
		"DATA_ERROR"
	};
	if ((quint8)status < Data::__LAST_STATUS__)
		debug << txtStatus[ status ];
	return debug;
 }

inline QDebug operator<<(QDebug debug, Data::Error error) {
	const char* txtErrors[] = {
		"NONE",
		"PERMITION_DENIED",
		"NOT_FOUND",
		"DATABASE_ERROR",
		"DATA_ALREADY_CHANGED",
		"INTERNAL_SERVER_ERROR"
	};
	if ((quint8)error < Data::__LAST_ERROR__)
		debug << txtErrors[ error ];
	return debug;
 }

#ifdef HORUS_SERVER
typedef Data ServerData;
Q_DECLARE_INTERFACE(ServerData, "net.horus.ServerData/1.0");
#endif
#ifdef HORUS_CLIENT
typedef Data ClientData;
Q_DECLARE_INTERFACE(ClientData, "net.horus.ClientData/1.0");
#endif

#endif // DATA_H

