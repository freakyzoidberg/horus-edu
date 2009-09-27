#ifndef MAILDATA_H
#define MAILDATA_H

#ifdef HORUS_SERVER
    #include <QtSql>
#endif
#ifdef HORUS_CLIENT
    #include <QVariant>
#endif
#include <QByteArray>
#include <QDateTime>
#include "../../Data.h"
#include "MailDataPlugin.h"
#include "MailItem.h"

class MailData : public Data
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerData)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientData)
#endif

  friend class MailDataPlugin;

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
        inline MailItemList&	items() { return _items; }

private:
        inline MailData(TreeData* node, MailDataPlugin* plugin) : Data(plugin) { _node = node; }
        inline ~MailData() {}

        MailItemList _items;
	TreeData*		   _node;
};

#endif // MAILDATA_H
