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
#ifndef SCHEDULEDATAPLUGIN_H
#define SCHEDULEDATAPLUGIN_H

#include <QDate>
#include "DataPlugin.h"

class TreeData;
class ScheduleData;
class ScheduleDataPlugin : public DataPlugin
{
    Q_OBJECT
#ifdef HORUS_SERVER
    Q_INTERFACES(ServerDataPlugin)
#endif
#ifdef HORUS_CLIENT
    Q_INTERFACES(ClientDataPlugin)
#endif

public:
        virtual ScheduleData*     schedule(quint32 scheduleId) = 0;
        virtual ScheduleData*     schedule(TreeData *node) = 0;
        virtual ScheduleData*	  newSchedule(TreeData* parent/*, QString name, UserData* user = 0*/) = 0;
//        virtual ScheduleData*	  nodeSchedule(quint32 nodeId) = 0;
//        virtual ScheduleData*	  nodeSchedule(TreeData* node) = 0;
//        virtual QList<ScheduleData*> nodeSchedules(TreeData* node, const QDate from = QDate(), const QDate to = QDate()) = 0;
        //virtual QList<ScheduleData*> userSchedules(UserData* user, const QDate from = QDate(), const QDate to = QDate()) = 0;
};

#ifdef HORUS_SERVER
typedef ScheduleDataPlugin ServerScheduleDataPlugin;
Q_DECLARE_INTERFACE(ServerScheduleDataPlugin, "net.horus.ServerScheduleDataPlugin/1.0");
#endif
#ifdef HORUS_CLIENT
typedef ScheduleDataPlugin ClientScheduleDataPlugin;
Q_DECLARE_INTERFACE(ClientScheduleDataPlugin, "net.horus.ClientScheduleDataPlugin/1.0");
#endif

#endif // SCHEDULEDATAPLUGIN_H
