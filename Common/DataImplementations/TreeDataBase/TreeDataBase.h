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
#ifndef TREEDATABASE_H
#define TREEDATABASE_H

#ifdef HORUS_SERVER
    #include <QtSql>
#endif
#ifdef HORUS_CLIENT
    #include <QVariant>
#endif
#include <QByteArray>
#include <QDateTime>
#include "../../Defines.h"
#include "../../TreeData.h"
#include "TreeDataBasePlugin.h"

class TreeDataBase : public TreeData
{
	Q_OBJECT
#ifdef HORUS_SERVER
	Q_INTERFACES(ServerTreeData)
#endif
#ifdef HORUS_CLIENT
	Q_INTERFACES(ClientTreeData)
#endif

	friend class TreeDataBasePlugin;
private:
	TreeDataBase(quint32 nodeId, TreeDataBasePlugin* plugin);
	inline ~TreeDataBase() {}

	quint32				_id;
	UserData*			_user;
	QString				_name;
	QString				_type;
	QList<TreeData*>	_children;
	TreeDataBase*		_parent;

public:
	// INTERFACE Data
	void				keyToStream(QDataStream& s) const;
	void				dataToStream(QDataStream& s) const;
	void				dataFromStream(QDataStream& s);

	bool				canChange(UserData* user) const;
	bool				canAccess(UserData* user) const;

	const QList<Data*>	dependsOfCreatedData() const;

	QDebug				operator<<(QDebug debug) const;


	// INTERFACE TreeData
	inline quint32		id() const { return _id; }

	TreeData*			createChild(const QString name, const QString type, UserData* user);

	inline const QString name() const { return _name; }
	void				setName(const QString name);

	inline UserData*	user() const { return _user; }
	void				setUser(UserData* user);

	inline const QString type() const { return _type; }
	void				setType(const QString type);

	inline TreeData*	parent() const { return _parent; }
	void				setParent(TreeData*);
	inline const QList<TreeData*>&	children() const { return _children; }

	bool				isDescendantOf(TreeData* parent);

#ifdef HORUS_CLIENT
	QVariant			data(int column, int role = Qt::DisplayRole) const;
	bool				dropMimeData(const QMimeData *, Qt::DropAction);
	const QIcon			icon() const;
#endif
#ifdef HORUS_SERVER
	quint8				serverRead();
	quint8				serverCreate();
	quint8				serverSave();
	quint8				serverRemove();
#endif

private slots:
	void thisRemoved();
	void userRemoved();
};

#endif // TREEDATABASE_H
