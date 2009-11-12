#ifndef ATTENDANCEDATABASEPLUGIN_H
#define ATTENDANCEDATABASEPLUGIN_H

#include <QHash>
#include "../../AttendanceDataPlugin.h"

class AttendanceDataBasePlugin : public AttendanceDataPlugin
{
	Q_OBJECT
#ifdef HORUS_SERVER
        Q_INTERFACES(ServerAttendanceDataPlugin)
#endif
#ifdef HORUS_CLIENT
        Q_INTERFACES(ClientAttendanceDataPlugin)
#endif

  friend class AttendanceDataBase;

public:
                     AttendanceDataBasePlugin() {}


private:

	//Plugin
public:
	inline const QString	pluginName() const { return "Event Data Base"; }
	inline const QString	pluginVersion() const { return "0.1"; }



	//DataPlugin
public:

#ifdef HORUS_SERVER
	void					loadData();
        QList<Data*>                            datasForUpdate(UserData* user, QDateTime date);
#endif
protected:
    //! Return the pointer to the Data with a his unique key read in the stream
	Data*					dataWithKey(QDataStream& s);
};

#endif // ATTENDANCEDATABASEPLUGIN_H
