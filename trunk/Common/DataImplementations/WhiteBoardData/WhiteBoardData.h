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
#include "WhiteBoardDataPlugin.h"

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
    void dataToStream(QDataStream& s);
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

	inline TreeData*        node() const { return (TreeData*)(parent()); }

private:
	inline WhiteBoardData(TreeData* node, WhiteBoardDataPlugin* plugin) : Data(plugin) { setParent(node); }
	inline ~WhiteBoardData() {}
};

#endif // WHITEBOARDDATA_H
