#ifndef TREEDATABASEPLUGIN_H
#define TREEDATABASEPLUGIN_H

#include <QHash>
#include "../../TreeDataPlugin.h"

class Data;
class TreeData;
class TreeDataBase;
class TreeDataBasePlugin : public TreeDataPlugin
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerTreeDataPlugin)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientTreeDataPlugin)
#endif

  friend class TreeDataBase;

public:
							TreeDataBasePlugin();		
	TreeData*				getNode(quint32 nodeId);
	TreeData*				createNewNode();
private:
	QHash<quint32,TreeData*>	nodes;


	//Plugin
public:
	inline const QString	pluginName() const { return "Tree Data Base"; }
	inline const QString	pluginVersion() const { return "0.1"; }


	//DataPlugin
public:
	inline const QString	getDataType() const { return "Tree"; }
	QList<Data*>			allDatas() const;
#ifdef HORUS_CLIENT
	void					dataHaveNewKey(Data*d, QDataStream& s);
#endif
#ifdef HORUS_SERVER
	void					loadData();
	void					userConnected(UserData* user, QDateTime date);
#endif
protected:
    //! Return the pointer to the Data with a his unique key read in the stream
	Data*					getDataWithKey(QDataStream& s);
};

#endif // TREEDATABASEPLUGIN_H