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
	WhiteBoardDataPlugin();
	WhiteBoardData*			whiteBoard(TreeData* node);
	WhiteBoardData*			whiteBoard(quint32 nodeId);


	//DataPlugin
public:
	inline const QString	dataType()   const { return "WhiteBoardData"; }
private:
    //! Return the pointer to the Data with a his unique key read in the stream
	Data*					dataWithKey(QDataStream& s);


	//Plugin
public:
	inline const QString	pluginName()    const { return "WhiteBoard Data Plugin"; }
	inline const QString	pluginVersion() const { return "0.1"; }
	void					load();
	void					unload();
	bool					canLoad() const;
};

#endif // WHITEBOARDDATAPLUGIN_H
