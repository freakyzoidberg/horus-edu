#ifndef WHITEBOARDDATAPLUGIN_H
#define WHITEBOARDDATAPLUGIN_H

#include <QHash>
#include "../../DataPlugin.h"

class Data;
class TreeData;
class WhiteBoardData;
class WhiteBoardDataPlugin : public DataPlugin
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerDataPlugin)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientDataPlugin)
#endif	

public:
	WhiteBoardData*			whiteBoard(TreeData* node);
	WhiteBoardData*			whiteBoard(quint32 nodeId);
private:
	QList<WhiteBoardData*>	_whiteBoards;


	//DataPlugin
public:
	inline const QString	dataType()   const { return "WhiteBoardData"; }
	QList<Data*>			allDatas() const;
#ifdef HORUS_SERVER
	void					loadData();
	QList<Data*>			datasForUpdate(UserData* user, QDateTime date);
#endif
private:
    //! Return the pointer to the Data with a his unique key read in the stream
	Data*					dataWithKey(QDataStream& s);


	//Plugin
public:
	inline const QString	pluginName()    const { return "WhiteBoard Data Plugin"; }
	inline const QString	pluginVersion() const { return "0.1"; }

};

#endif // WHITEBOARDDATAPLUGIN_H
