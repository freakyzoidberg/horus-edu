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
#ifndef SCHEDULEDATABASE_H
#define SCHEDULEDATABASE_H

#ifdef HORUS_SERVER
    #include <QtSql>
#endif
#ifdef HORUS_CLIENT
    #include <QVariant>
#endif
#include <QByteArray>
#include <QDate>
#include "../../Defines.h"
#include "../../ScheduleData.h"
#include "ScheduleDataBasePlugin.h"
#include "ScheduleItem.h"

class ScheduleDataBase : public ScheduleData
{
	Q_OBJECT
#ifdef HORUS_SERVER
        Q_INTERFACES(ServerScheduleData)
#endif
#ifdef HORUS_CLIENT
        Q_INTERFACES(ClientScheduleData)
#endif

  friend class			ScheduleDataBasePlugin;

private:
        ScheduleDataBase(TreeData* node, ScheduleDataBasePlugin* plugin);
        ~ScheduleDataBase() {}

        QDate                           _startDate;
        QDate                           _endDate;
        QList<ScheduleItem* >           _sEvents;
        QList<ScheduleException* >      _sException;
	TreeData*			_node;


        // INTERFACE ScheduleData
public:
        inline QDate                        startDate() const					{ return _startDate; }
        inline void                         setStartDate(const QDate& date)	{ QMutexLocker M(&mutex); _startDate = date; }
        inline QDate                        endDate() const						{ return _endDate; }
        inline void                         setEndDate(const QDate& date) { QMutexLocker M(&mutex); _endDate = date; }
        inline QList<ScheduleException* >   scheduleException() const						{ return _sException; }
        inline void                         addException(ScheduleException* excp) { QMutexLocker M(&mutex); _sException.append(excp); }
        inline void                         removeException(ScheduleException* excp) { QMutexLocker M(&mutex); _sException.removeOne(excp); }
        inline QList<ScheduleItem* >        scheduleEvents() const						{ return _sEvents; }
        inline void                         addEvent(ScheduleItem* event) { QMutexLocker M(&mutex); _sEvents.append(event); }
        inline void                         removeEvent(ScheduleItem* event) { QMutexLocker M(&mutex); _sEvents.removeOne(event); }
        inline TreeData*                    node() const						{ return _node; }


	//INTERFACE Data
public:
	void				keyToStream(QDataStream& s) const;
	void				dataToStream(QDataStream& s) const;
	void				dataFromStream(QDataStream& s);

	bool				canChange(UserData* user) const;
	bool				canAccess(UserData* user) const;

        const QList<Data*>              dependsOfCreatedData() const;

	QDebug				operator<<(QDebug debug) const;

#ifdef HORUS_SERVER
public:
	quint8				serverRead();
	quint8				serverCreate();
	quint8				serverSave();
	quint8				serverRemove();
#endif
};

#endif // SCHEDULEDATABASE_H
