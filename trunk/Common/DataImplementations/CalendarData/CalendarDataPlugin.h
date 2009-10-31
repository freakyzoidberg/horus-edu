#ifndef WHITEBOARDDATAPLUGIN_H
#define WHITEBOARDDATAPLUGIN_H

#include <QHash>
#include "../../DataPlugin.h"

class Data;
class TreeData;
class CalendarData;
class CalendarDataPlugin : public DataPlugin
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerDataPlugin)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientDataPlugin)
#endif	

public:
        CalendarData*			getCalendar(TreeData* node);
        CalendarData*			getCalendar(quint32 nodeId);
private:
        QList<CalendarData*>	whiteBoards;


	//DataPlugin
public:
        inline const QString	getDataType()   const { return "CalendarData"; }
	QList<Data*>			allDatas() const;
#ifdef HORUS_SERVER
	void					loadData();
	QList<Data*>			datasForUpdate(UserData* user, QDateTime date);
#endif
private:
    //! Return the pointer to the Data with a his unique key read in the stream
	Data*					getDataWithKey(QDataStream& s);


	//Plugin
public:
        inline const QString	pluginName()    const { return "Calendar Data Plugin"; }
	inline const QString	pluginVersion() const { return "0.1"; }

};

#endif // WHITEBOARDDATAPLUGIN_H
