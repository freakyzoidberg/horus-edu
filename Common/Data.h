#ifndef DATA_H
#define DATA_H

#include "DataPlugin.h"
#include <QDataStream>

class Data : public QObject
{
  Q_OBJECT

  enum DataStatus { EMPTY, UPDATING, SAVING, CREATING, DELETING, CACHED, UPTODATE, CREATED, DELETED };
  enum Error { NONE=0, PERMITION_DENIED=1, NOT_FOUND=2, DATABASE_ERROR=3, DATA_ALREADY_CHANGED=4 };
  static inline const char* errorMessage() {  }

protected:
    inline Data(DataPlugin* _plugin, DataStatus _status=EMPTY) { plugin=_plugin; status=_status; error=NONE; }
    inline ~Data() {}

public:
    inline const QString getType() const { return plugin->getDataType(); }

    //! Have to write his key into the stream to be able to identify this data with the server and the cache.
    virtual void keyToStream(QDataStream& s) = 0;
    //! Have to write his data into the stream.
    /*! Called to:
     *  - Transfert this data between client and server.
     *  - Write to a local cache file.
     *  - Compare two data.
     */
    virtual void dataToStream(QDataStream& s) = 0;
    //! Have to read his data from the stream.
    /*! Called to:
     *  - Transfert this data between client and server.
     *  - Read from a local cache file.
     */
    virtual void dataFromStream(QDataStream& s) = 0;
    //! Usefull for debuging. Not mandatory but important.
    virtual QDebug operator<<(QDebug debug) { return debug << getType(); }
#ifdef HORUS_CLIENT
public:
    virtual QVariant getValue(int column, int role) = 0;
    //! Function just set the UPDATING status if not already uptodate or updating
    inline void update()
        { if (status == EMPTY || status == UPTODATE || status == CACHED) setStatus(UPDATING); }
signals:
    //! Signal emmited when the data is updated.
    void updated();
#else
#ifdef HORUS_SERVER
public:
    //! Fill the current data with a defined key from teh database.
    virtual void fillFromDatabase  (QSqlQuery&) = 0;
    //! Create this data into the database, and update the key.
    virtual void createIntoDatabase(QSqlQuery&) = 0;
    //! Save the current data into the database.
    virtual void saveIntoDatabase  (QSqlQuery&) = 0;
    //! Delete the current data from the database.
    virtual void deleteFromDatabase(QSqlQuery&) = 0;
#else
#error "You must define HORUS_CLIENT or HORUS_SERVER in your project."
#endif

public:
    //! Return the current status of this data.
    inline DataStatus  status() const { return status; }
    //! Change the current status and tell the coresponding plugin the data just changed.
    inline void        setStatus(DataStatus _status)
        { DataStatus old=status; status=_status; plugin->dataStatusChange(this, old); }

protected:
    DataPlugin*   plugin;
    quint8        status;
    quint8        error;
};

inline QDebug operator<<(QDebug debug, const IData& data) { return data << debug; }

#endif // DATA_H
