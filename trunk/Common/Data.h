#ifndef DATA_H
#define DATA_H

#ifdef HORUS_CLIENT
  #include <QColor>
#endif

#include <QMutex>
#include <QMutexLocker>
#include <QDataStream>
#include <QString>
#include <QDebug>
#include <QVariant>
#include <QDateTime>

#include "DataPlugin.h"
#include "DataManager.h"
#include "PluginManager.h"

class UserData;
class Data : public QObject
{
  Q_OBJECT
#ifdef HORUS_SERVER
  friend class DataManagerServer;
#endif
#ifdef HORUS_CLIENT
  friend class DataManagerClient;
  friend class UserCache;
#endif

public:
	// Data streamed between Client and Server:    V->value     N->new key     E->error
	//                          //   Client|Server|Client |Server
	//                          //     to  |  to  |-Memory|-Memory
	//                          //   Server|Client|-Cache |
	enum DataStatus { EMPTY,    // 0       |      |   X   |  X
					  CACHED,   // 1       |      |   X   |
					  UPTODATE, // 2       |      |   X   |  X
					  UPDATING, // 3  X    |      |   X   |
					  SAVING,   // 4  X  V |      |   X   |
					  CREATING, // 5  X  V |      |   X   |
					  DELETING, // 6  X    |      |   X   |
					  UPDATED,  // 7       | X  V |       |
					  SAVED,    // 8       | X    |       |
					  CREATED,  // 9       | X  N |       |
					  DELETED,  //10       | X    |       |  X
					  ERROR};   //11       | X  E |       |

	enum Error { NONE, PERMITION_DENIED, NOT_FOUND, DATABASE_ERROR, DATA_ALREADY_CHANGED, INTERNAL_SERVER_ERROR, __LAST_ERROR__ };

	inline const QString    dataType() const { return _plugin->dataType(); }


    //! Have to write his key into the stream to be able to identify this data with the server and the cache.
    virtual void            keyToStream(QDataStream& s) = 0;
    //! Have to write his data into the stream.
    /*! Called to:
     *  - Transfert this data between client and server.
     *  - Write to a local cache file.
     *  - Compare two data.
     */
	virtual inline void     dataToStream(QDataStream& s) const { s << _lastChange; }
    //! Have to read his data from the stream.
    /*! Called to:
     *  - Transfert this data between client and server.
     *  - Read from a local cache file.
     */
    virtual inline void     dataFromStream(QDataStream& s) { s >> _lastChange; }

    //! Return the current status of this data.
    inline quint8           status() const { return (quint8)_status; }
    //! Change the current status and tell the coresponding plugin the data just changed.
	inline void             setStatus(quint8 status) { QMutexLocker M(&mutex); _plugin->dataManager->dataStatusChange(this, status); }

    inline const QDateTime lastChange() { return _lastChange; }

#ifdef HORUS_CLIENT
	inline bool canAccess() { return canAccess(_plugin->pluginManager->currentUser()); }
	inline bool canChange() { return canChange(_plugin->pluginManager->currentUser()); }
#endif
	virtual inline bool canChange(UserData*) { return true; }
	virtual inline bool canAccess(UserData*) { return true; }

public slots:
	//! Function to create the value of the data
	virtual inline void		create() { setStatus(CREATING); }

	//! Function to save the value of the data
	virtual inline void		save() { setStatus(SAVING); }

	//! Function to delete the value of the data
	virtual inline void		remove() { setStatus(DELETING); }

signals:
	//! Signal emmited when the data is created.
	void                    created();
	//! Signal emmited when the data is updated.
		void                updated();
	//! Signal emmited when the data is removed.
	void                    removed();
	//! Signal emmited when an error append on this data
	void                    error(quint8 error);

public:
    //! Usefull for debuging. Not mandatory but important.
	virtual inline QDebug   operator<<(QDebug debug) const { return debug << dataType(); }
#ifdef HORUS_CLIENT
    virtual inline QVariant data(int, int role = Qt::DisplayRole) const
    {
        if (role == Qt::BackgroundColorRole)
        {
            if (status() == UPTODATE)
                return QColor(210, 255, 210);//green : uptodate
            if (status() == SAVING || status() == CREATING)
                return QColor(210, 210, 255);//blue : saving & creating
            if (status() == DELETING)
                return QColor(255, 210, 210);//red : deleting

            return QColor(220, 220, 220);//gray : cached, updating, ...
        }
        return QVariant();
    }

    //! Function just set the UPDATING status if not already uptodate or updating
    inline void             update()
        { if (_status == EMPTY || _status == UPTODATE || _status == CACHED) setStatus(UPDATING); }
#endif
#ifdef HORUS_SERVER
	//! Fill the current data with a defined key from the database.
	virtual inline quint8     serverRead() { return NOT_FOUND; }
    //! Create this data into the database, and update the key.
	virtual        quint8     serverCreate() = 0;
    //! Save the current data into the database.
	virtual        quint8     serverSave() = 0;
    //! Delete the current data from the database.
	virtual        quint8     serverRemove() = 0;
	//! send this data to a user
	inline void				  sendToUser(UserData* user) { _plugin->dataManager->sendData(user, this); }
#endif

protected:
	inline Data(DataPlugin* plugin) : mutex(QMutex::Recursive) { _plugin=plugin; _status=EMPTY; }
	inline ~Data() {}

    DataPlugin*             _plugin;
    quint8                  _status;
    QDateTime               _lastChange;

public:
	QMutex                  mutex;
};

inline QDebug operator<<(QDebug debug, const Data& data) { return data << debug; }
inline QDebug operator<<(QDebug debug, const Data* data) { if (data) return (*data) << debug; else return debug << "null"; }
inline QDebug operator<<(QDebug debug, Data::DataStatus status) {
	static const quint8 nbrStatus = 12;
	static const char*  txtStatus[] = {
		"EMPTY",
		"CACHED",
		"UPTODATE",
		"UPDATING",
		"SAVING",
		"CREATING",
		"DELETING",
		"UPDATED",
		"SAVED",
		"CREATED",
		"DELETED",
		"ERROR"
	};
	if ((quint8)status < nbrStatus)
		debug << txtStatus[ status ];
	return debug;
 }

inline QDebug operator<<(QDebug debug, Data::Error error) {
	static const quint8 nbrErrors = 12;
	static const char*  txtErrors[] = {
		"NONE",
		"PERMITION_DENIED",
		"NOT_FOUND",
		"DATABASE_ERROR",
		"DATA_ALREADY_CHANGED",
		"INTERNAL_SERVER_ERROR"
	};
	if ((quint8)error < nbrErrors)
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

