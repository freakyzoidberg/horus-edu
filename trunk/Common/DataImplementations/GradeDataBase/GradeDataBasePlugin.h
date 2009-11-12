#ifndef GRADEDATABASEPLUGIN_H
#define GRADEDATABASEPLUGIN_H

#include <QHash>
#include "../../GradeDataPlugin.h"

class GradeDataBasePlugin : public GradeDataPlugin
{
	Q_OBJECT
#ifdef HORUS_SERVER
        Q_INTERFACES(ServerGradeDataPlugin)
#endif
#ifdef HORUS_CLIENT
        Q_INTERFACES(ClientGradeDataPlugin)
#endif

  friend class GradeDataBase;

public:
                                                        GradeDataBasePlugin() {}

private:


	//Plugin
public:
	inline const QString	pluginName() const { return "Event Data Base"; }
	inline const QString	pluginVersion() const { return "0.1"; }



	//DataPlugin
public:

#ifdef HORUS_SERVER
	void					loadData();
	QList<Data*>			datasForUpdate(UserData* user, QDateTime date);
#endif
protected:
    //! Return the pointer to the Data with a his unique key read in the stream
	Data*					dataWithKey(QDataStream& s);
};

#endif // GRADEDATABASEPLUGIN_H
