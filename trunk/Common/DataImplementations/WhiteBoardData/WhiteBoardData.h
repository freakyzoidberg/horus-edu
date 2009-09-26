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
#include "WhiteBoardDataPlugin.h"
#include "WhiteBoardItem.h"

class WhiteBoardData : public Data
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerData)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientData)
#endif

  friend class WhiteBoardDataPlugin;

public:
    // Data Interface
    void keyToStream(QDataStream& s);
	void dataToStream(QDataStream& s) const;
    void dataFromStream(QDataStream& s);
    QDebug operator<<(QDebug debug) const;
#ifdef HORUS_CLIENT
    QVariant data(int column, int role = Qt::DisplayRole) const;
#endif
#ifdef HORUS_SERVER
    void fillFromDatabase  (QSqlQuery&);
    void createIntoDatabase(QSqlQuery&);
    void saveIntoDatabase  (QSqlQuery&);
    void deleteFromDatabase(QSqlQuery&);
#endif


	inline TreeData*			node() const { return _node;  }
	inline WhiteBoardItemList&	items() { return _items; }

private:
	inline WhiteBoardData(TreeData* node, WhiteBoardDataPlugin* plugin) : Data(plugin) { _node = node; }
	inline ~WhiteBoardData() {}

	WhiteBoardItemList _items;
	TreeData*		   _node;
};

#endif // WHITEBOARDDATA_H
