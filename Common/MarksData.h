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
#ifndef MARKSDATA_H
#define MARKSDATA_H

#include "Data.h"
#include "ExamsData.h"
#include "MarksDataPlugin.h"

class MarksData : public Data
{
	Q_OBJECT
#ifdef HORUS_SERVER
	Q_INTERFACES(ServerData)
#endif
#ifdef HORUS_CLIENT
			Q_INTERFACES(ClientData)
#endif

public:
	inline quint32		id() const { return _id; }

	virtual QString		comment()  = 0;
	virtual void		setComment(const QString& comment)  = 0;

	virtual void		setResult(const QString& result)  = 0;
	virtual QString		result()  = 0;

	virtual quint32		student() const  = 0;
	virtual void		setStudent(const quint32 id)  = 0;

	virtual ExamsData*	exam() const = 0;
	virtual	void			setExam(ExamsData* exam) = 0;

	virtual MarksData*	mark() const = 0;
	virtual	void			setMark(MarksData* mark) =  0;

protected:
	inline				MarksData(quint32 id, MarksDataPlugin* plugin) : Data(plugin) { _id = id; }
	inline				~MarksData() {}
	quint32				_id;
};

#ifdef HORUS_SERVER
typedef MarksData ServerMarksData;
Q_DECLARE_INTERFACE(ServerMarksData, "net.horus.ServerMarksData/1.0");
#endif
#ifdef HORUS_CLIENT
typedef MarksData ClientMarksData;
Q_DECLARE_INTERFACE(ClientMarksData, "net.horus.ClientMarksData/1.0");
#endif

#endif // MARKSDATA_H
