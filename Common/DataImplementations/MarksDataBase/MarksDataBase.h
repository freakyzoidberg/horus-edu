#ifndef MARKSDATABASE_H
#define MARKSDATABASE_H

#ifdef HORUS_SERVER
    #include <QtSql>
#endif
#ifdef HORUS_CLIENT
    #include <QVariant>
#endif
#include <QByteArray>
#include <QDateTime>
#include "../../Defines.h"
#include "../../MarksData.h"
#include "MarksDataBasePlugin.h"

class MarksDataBase : public MarksData
{
	Q_OBJECT
#ifdef HORUS_SERVER
        Q_INTERFACES(ServerMarksData)
#endif
#ifdef HORUS_CLIENT
        Q_INTERFACES(ClientMarksData)
#endif

  friend class			MarksDataBasePlugin;

private:
                                                MarksDataBase(MarksDataBasePlugin* plugin);
        inline				~MarksDataBase() {}


        // INTERFACE MarksData
public:



	//INTERFACE Data
public:
	void				keyToStream(QDataStream& s);
	void				dataToStream(QDataStream& s) const;
	void				dataFromStream(QDataStream& s);

	QDebug				operator<<(QDebug debug) const;

#ifdef HORUS_CLIENT
	QVariant			data(int column, int role = Qt::DisplayRole) const;
public slots:
	void				create();
#endif
#ifdef HORUS_SERVER
public:
	quint8				serverRead();
	quint8				serverCreate();
	quint8				serverSave();
	quint8				serverRemove();
#endif
};

#endif // MARKSDATABASE_H
