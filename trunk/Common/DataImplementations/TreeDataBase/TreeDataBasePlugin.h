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
	TreeDataBasePlugin() { _rootNode = node(0); }
	inline TreeData*		rootNode() { return _rootNode; }
	TreeData*				node(quint32 nodeId);
	TreeData*				createNode();
private:
	QHash<quint32,TreeData*> _nodes;
	TreeData*				_rootNode;


	//Plugin
public:
	inline const QString	pluginName() const { return "Tree Data Base"; }
	inline const QString	pluginVersion() const { return "0.1"; }


	//DataPlugin
public:
	inline const QString	dataType() const { return "Tree"; }
	QList<Data*>			allDatas() const;
#ifdef HORUS_CLIENT
	void					dataHaveNewKey(Data*d, QDataStream& s);
#endif
#ifdef HORUS_SERVER
	void					loadData();
	QList<Data*>			datasForUpdate(UserData* user, QDateTime date);
#endif
protected:
    //! Return the pointer to the Data with a his unique key read in the stream
	Data*					dataWithKey(QDataStream& s);
};

#endif // TREEDATABASEPLUGIN_H
