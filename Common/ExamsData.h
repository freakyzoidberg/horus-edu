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
#ifndef EXAMSDATA_H
#define EXAMSDATA_H

#include "Data.h"
#include "ExamsDataPlugin.h"

class ExamsData : public Data
{
	Q_OBJECT
#ifdef HORUS_SERVER
	Q_INTERFACES(ServerData)
#endif
#ifdef HORUS_CLIENT
	Q_INTERFACES(ClientData)
#endif

public:
	virtual	QString		comment() = 0;
	virtual void		setComment(const QString& comment) = 0;

	virtual void		setDate(const QDate& date) = 0;
	virtual QDate		date() = 0;

	virtual TreeData*	subject() const = 0;

	virtual quint32		teacher() const = 0;
	virtual void		setTeacher(const quint32 id) = 0;

protected:
	inline				ExamsData(quint32 id, ExamsDataPlugin* plugin) : Data(plugin) { _id = id; }
	inline				~ExamsData() {}
	quint32				_id;
};

#ifdef HORUS_SERVER
typedef ExamsData ServerExamsData;
Q_DECLARE_INTERFACE(ServerExamsData, "net.horus.ServerExamsData/1.0");
#endif
#ifdef HORUS_CLIENT
typedef ExamsData ClientExamsData;
Q_DECLARE_INTERFACE(ClientExamsData, "net.horus.ClientExamsData/1.0");
#endif

#endif // EXAMSDATA_H
