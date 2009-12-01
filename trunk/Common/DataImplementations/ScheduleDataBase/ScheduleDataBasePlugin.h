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
#ifndef SCHEDULEDATABASEPLUGIN_H
#define SCHEDULEDATABASEPLUGIN_H

#include <QHash>
#include "../../ScheduleDataPlugin.h"

class ScheduleDataBasePlugin : public ScheduleDataPlugin
{
	Q_OBJECT
#ifdef HORUS_SERVER
        Q_INTERFACES(ServerScheduleDataPlugin)
#endif
#ifdef HORUS_CLIENT
        Q_INTERFACES(ClientScheduleDataPlugin)
#endif

  friend class ScheduleDataBase;

public:
                                                        ScheduleDataBasePlugin();

        ScheduleData*				newSchedule(TreeData* parent/*, QString name, UserData* user = 0*/);
        ScheduleData*				nodeSchedule(quint32 nodeId);
        ScheduleData*				nodeSchedule(TreeData* node);
        QList<ScheduleData*>                    nodeSchedules(TreeData* node, const QDate from = QDate(), const QDate to = QDate());
//      QList<ScheduleData*>                    userSchedules(UserData* user, const QDate from = QDate(), const QDate to = QDate());

private:
        void					recursiveTreeSearch(QList<ScheduleData*>& list, TreeData* node, const QDate& from, const QDate& to);


	//Plugin
public:
        inline const QString                    pluginName() const { return "Schedule Data Base"; }
        inline const QString                    pluginVersion() const { return "0.1"; }
	bool					canLoad() const;
	void					load();
	void					unload();


	//DataPlugin
public:
        inline const QString	dataType() const { return "Schedule"; }
#ifdef HORUS_SERVER
	QList<Data*>			datasForUpdate(UserData* user, QDateTime date);
#endif

protected:
    //! Return the pointer to the Data with a his unique key read in the stream
	Data*					dataWithKey(QDataStream& s);
};

#endif // SCHEDULEDATABASEPLUGIN_H
