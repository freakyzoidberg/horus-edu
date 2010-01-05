/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
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
	QStringList				subjects() const;
	QList<TreeData*>		grades() const;
#ifdef HORUS_CLIENT
	inline QAbstractItemModel*	treeModel() const { return _treeModel; }
	inline QAbstractListModel*	listModel() const { return _listModel; }
private:
	QAbstractItemModel*		_treeModel;
	QAbstractListModel*		_listModel;
#endif


public:
	TreeDataBasePlugin();
private:
	TreeData*				_rootNode;
};

#endif // TREEDATABASEPLUGIN_H
