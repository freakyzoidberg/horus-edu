#ifndef WHITEBOARDDATA_H
#define WHITEBOARDDATA_H

#ifdef HORUS_SERVER
    #include <QtSql>
#endif
#ifdef HORUS_CLIENT
    #include <QVariant>
#endif
#include <QByteArray>
#include <QDateTime>
#include "../../Data.h"
#include "CalendarDataPlugin.h"
#include "CalendarItem.h"

class CalendarData : public Data
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerData)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientData)
#endif

  friend class CalendarDataPlugin;

public:
	enum SyncMode { NO_SYNC, SEMI_SYNC, FULL_SYNC };

    // Data Interface
    void keyToStream(QDataStream& s);
    void dataToStream(QDataStream& s) const;
    void dataFromStream(QDataStream& s);
    QDebug operator<<(QDebug debug) const;
#ifdef HORUS_CLIENT
    QVariant data(int column, int role = Qt::DisplayRole) const;
#endif
#ifdef HORUS_SERVER
	quint8     serverRead();
	quint8     serverCreate();
	quint8     serverSave();
	quint8     serverRemove();
#endif


	inline TreeData*			node() const { return _node;  }
#ifdef HORUS_CLIENT
        inline CalendarItemList&	items() { return _items; }
#endif
	inline SyncMode				syncMode() const { return (SyncMode)_syncMode; }
	inline void					setSyncMode(SyncMode mode) { _syncMode = (quint8)mode; }

private:
        inline CalendarData(TreeData* node, CalendarDataPlugin* plugin) : Data(plugin) { _node = node; }
        inline ~CalendarData() {}

#ifdef HORUS_CLIENT
        CalendarItemList _items;
#endif
#ifdef HORUS_SERVER
	// on the server, do not de-serialize, keep binary to put it in database
	QByteArray		   _items;
#endif
	TreeData*		   _node;
	quint8			   _syncMode;
};

#endif // WHITEBOARDDATA_H
