#ifndef MARKSDATABASEPLUGIN_H
#define MARKSDATABASEPLUGIN_H

#include <QHash>
#include "../../MarksDataPlugin.h"

class MarksDataBasePlugin : public MarksDataPlugin
{
	Q_OBJECT
#ifdef HORUS_SERVER
        Q_INTERFACES(ServerMarksDataPlugin)
#endif
#ifdef HORUS_CLIENT
        Q_INTERFACES(ClientMarksDataPlugin)
#endif

  friend class MarksDataBase;

public:
                                                        MarksDataBasePlugin() {}

private:


	//Plugin
public:
	inline const QString	pluginName() const { return "Event Data Base"; }
	inline const QString	pluginVersion() const { return "0.1"; }



	//DataPlugin
public:
	inline const QString	dataType() const { return "Event"; }
	QList<Data*>			allDatas() const { return _allEvents; }
#ifdef HORUS_SERVER
	void					loadData();
	QList<Data*>			datasForUpdate(UserData* user, QDateTime date);
#endif
protected:
    //! Return the pointer to the Data with a his unique key read in the stream
	Data*					dataWithKey(QDataStream& s);
};

#endif // MarksDataBASEPLUGIN_H
