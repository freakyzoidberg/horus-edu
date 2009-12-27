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
#ifndef EXAMSDATAPLUGIN_H
#define EXAMSDATAPLUGIN_H

#include <QDateTime>
#include "DataPlugin.h"

class TreeData;
class ExamsData;
class ExamsDataPlugin : public DataPlugin
{
    Q_OBJECT
#ifdef HORUS_SERVER
    Q_INTERFACES(ServerDataPlugin)
#endif
#ifdef HORUS_CLIENT
    Q_INTERFACES(ClientDataPlugin)
#endif

public:
	virtual ExamsData*	  newExams(TreeData* parent, QString name, UserData* user = 0) = 0;
	virtual ExamsData*	  exam(quint32 nodeId) = 0;
	//virtual QList<ExamsData*> userExams(TreeData* node) = 0;


		//Plugin
public:
	inline const QString	pluginName() const { return "ExamsDataPlugin"; }
	inline const QString	dataType() const { return "Exams"; }

};

#ifdef HORUS_SERVER
typedef ExamsDataPlugin ServerExamsDataPlugin;
Q_DECLARE_INTERFACE(ServerExamsDataPlugin, "net.horus.ServerExamsDataPlugin/1.0");
#endif
#ifdef HORUS_CLIENT
typedef ExamsDataPlugin ClientExamsDataPlugin;
Q_DECLARE_INTERFACE(ClientExamsDataPlugin, "net.horus.ClientExamsDataPlugin/1.0");
#endif

#endif // EXAMSDATAPLUGIN_H
