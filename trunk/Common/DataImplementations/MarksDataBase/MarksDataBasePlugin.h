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
#ifndef MARKSDATABASEPLUGIN_H
#define MARKSDATABASEPLUGIN_H

#include <QHash>
#include "../../MarksDataPlugin.h"
#include "../../ExamsData.h"
#include "../../UserData.h"

class MarksDataBasePlugin : public MarksDataPlugin
{
	Q_OBJECT
#ifdef HORUS_SERVER
	Q_INTERFACES(ServerMarksDataPlugin)
#endif
#ifdef HORUS_CLIENT
	Q_INTERFACES(ClientMarksDataPlugin)
#endif

  friend class MarksDataBase;

public:
							MarksDataBasePlugin();

	MarksData*				newMarks(ExamsData* parent, UserData* user = 0);
	MarksData*				mark(quint32 nodeId);

	//Plugin
public:
	inline const QString	pluginName() const { return "Marks Data Base"; }
	inline const QString	pluginVersion() const { return "0.1"; }
	bool					canLoad() const;
	void					load();
	void					unload();
	//DataPlugin
public:
	inline const QString	dataType() const { return "Marks"; }
#ifdef HORUS_SERVER
	QList<Data*>			datasForUpdate(MarksData* user, QDateTime date);
#endif
#ifdef HORUS_CLIENT
	QAbstractListModel*		listModel() const;
	void					dataHaveNewKey(Data*d, QDataStream& s);
#endif

protected:
    //! Return the pointer to the Data with a his unique key read in the stream
	Data*					dataWithKey(QDataStream& s);
};

#endif // MARKSDATABASEPLUGIN_H
