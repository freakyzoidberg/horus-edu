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



	//Plugin
public:
	inline const QString	pluginName() const { return "Tree Data Base"; }
	inline const QString	pluginVersion() const { return "0.1"; }
	void					load();
	void					unload();
	bool					canLoad() const;



	//DataPlugin
public:
	inline const QString	dataType() const { return "Tree"; }
#ifdef HORUS_CLIENT
	void					dataHaveNewKey(Data*d, QDataStream& s);
#endif
protected:
    //! Return the pointer to the Data with a his unique key read in the stream
	Data*					dataWithKey(QDataStream& s);



	//TreeDataPlugin
public:
	inline TreeData*		rootNode() const { return _rootNode; }
	TreeData*				node(quint32 nodeId);
	TreeData*				createNode();
#ifdef HORUS_CLIENT
	QAbstractItemModel*		treeModel() const;
	QAbstractListModel*		listModel() const;
#endif



	TreeDataBasePlugin();
private:
	TreeData*				_rootNode;
};

#endif // TREEDATABASEPLUGIN_H
