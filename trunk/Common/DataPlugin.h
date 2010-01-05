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
#ifndef DATAPLUGIN_H
#define DATAPLUGIN_H

#include "QByteArray"
#include "Plugin.h"
#include "MetaPlugin.h"

#ifdef HORUS_CLIENT
class QAbstractListModel;
#endif

class Data;
class UserData;
class DataManager;

//! this object have to references these own data in memory (if needed) and to provide an interface to the other plugins to access these
/*!
 * run in the data thread
 */
class DataPlugin : public Plugin
{
	Q_OBJECT
	Q_INTERFACES(Plugin)
	friend class Data;
	friend class MetaPlugin;

public:
	//! contains the data manager, filled by the core juste before Plugin::canLoad() call.
	DataManager*						dataManager;

	//! return the type of the data
	virtual const QString				dataType() const = 0;
    //! Return the pointer to the Data with a his unique key read in the stream
	virtual Data*						dataWithKey(QDataStream&) = 0;

	//! called by the UserCache to put every data into the cache
	inline const QList<Data*>&			allDatas() const { return _allDatas; }

#ifdef HORUS_CLIENT
	friend class DataManagerClient;
	friend class PluginManagerClient;
	friend class UserCache;
public:
	//! On the client, when creating a new data, the key can change. So this function have to update the data with the new key in the stream
	virtual inline void					dataHaveNewKey(Data*, QDataStream&) {};
	//! return a list model for the data
	virtual inline QAbstractListModel*	listModel() const { return 0; }
#endif
#ifdef HORUS_SERVER
	friend class DataManagerServer;
public:
	virtual inline void					userConnected(UserData*) {}
	virtual inline void					userDisconnected(UserData*) {}
#endif

// theses signals are emmited byt the dataManager, so not nessesary to emit them
// the same signals are also emmited on the data itself
signals:
	void								dataCreated      (Data* data);
	void								dataUpdated      (Data* data);
	void								dataRemoved      (Data* data);
	void								dataStatusChanged(Data* data);
	void								dataError        (Data* data, quint8 error);


protected:
	inline DataPlugin() {}
	virtual inline ~DataPlugin() {}
	QList<Data*>						_allDatas;
};

#ifdef HORUS_SERVER
typedef DataPlugin ServerDataPlugin;
Q_DECLARE_INTERFACE(ServerDataPlugin, "net.horus.ServerDataPlugin/1.0");
#endif
#ifdef HORUS_CLIENT
typedef DataPlugin ClientDataPlugin;
Q_DECLARE_INTERFACE(ClientDataPlugin, "net.horus.ClientDataPlugin/1.0");
#endif

#endif // DATAPLUGIN_H
