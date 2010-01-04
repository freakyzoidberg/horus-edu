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
#ifndef WHITEBOARDDATA_H
#define WHITEBOARDDATA_H

#ifdef HORUS_SERVER
    #include <QtSql>
#endif
#ifdef HORUS_CLIENT
    #include <QVariant>
#endif
#include <QByteArray>
#include <QDateTime>
#include "../../Data.h"
#include "WhiteBoardDataPlugin.h"
#include "WhiteBoardItem.h"

class WhiteBoardData : public Data
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerData)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientData)
#endif

  friend class WhiteBoardDataPlugin;

public:
	enum						SyncMode { NO_SYNC, SEMI_SYNC, FULL_SYNC };

    // Data Interface
	void						keyToStream(QDataStream& s) const;
	void						dataToStream(QDataStream& s) const;
	void						dataFromStream(QDataStream& s);

	bool						canChange(UserData* user) const;
	bool						canAccess(UserData* user) const;

	const QList<Data*>			dependsOfCreatedData() const;

	QDebug						operator<<(QDebug debug) const;
#ifdef HORUS_CLIENT
	QVariant					data(int column, int role = Qt::DisplayRole) const;
#endif
#ifdef HORUS_SERVER
	quint8						serverCreate();
	quint8						serverSave();
	quint8						serverRemove();
#endif


	inline TreeData*			node() const { return _node;  }
#ifdef HORUS_CLIENT
	inline WhiteBoardItemList&	items() { return _items; }
#endif
	inline SyncMode				syncMode() const { return _syncMode; }
	inline void					setSyncMode(SyncMode mode) { QMutexLocker M(&mutex); _syncMode = mode; }

private:
	WhiteBoardData(TreeData* node, WhiteBoardDataPlugin* plugin);
	inline ~WhiteBoardData() {}

#ifdef HORUS_CLIENT
	WhiteBoardItemList			_items;
#endif
#ifdef HORUS_SERVER
	// on the server, do not de-serialize, keep binary to put it in database
	QByteArray					_items;
#endif
	TreeData*					_node;
	SyncMode					_syncMode;
};

#endif // WHITEBOARDDATA_H
