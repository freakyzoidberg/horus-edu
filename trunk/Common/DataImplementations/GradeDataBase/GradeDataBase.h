#ifndef GRADEDATABASE_H
#define GRADEDATABASE_H

#ifdef HORUS_SERVER
    #include <QtSql>
#endif
#ifdef HORUS_CLIENT
    #include <QVariant>
#endif
#include <QByteArray>
#include <QDateTime>
#include "../../Defines.h"
#include "../../GradeData.h"
#include "GradeDataBasePlugin.h"

class GradeDataBase : public GradeData
{
	Q_OBJECT
#ifdef HORUS_SERVER
        Q_INTERFACES(ServerGradeData)
#endif
#ifdef HORUS_CLIENT
        Q_INTERFACES(ClientGradeData)
#endif

  friend class			GradeDataBasePlugin;

private:
                                                GradeDataBase(TreeData* node, GradeDataBasePlugin* plugin);
        inline				~GradeDataBase() {}


        // INTERFACE GradeData
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

#endif // GRADEDATABASE_H
