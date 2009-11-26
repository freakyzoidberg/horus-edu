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
#ifndef MAILDATA_H
#define MAILDATA_H

#include "Data.h"
#include "DataPlugin.h"
#include "MailDataPlugin.h"

class MailData : public Data
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerData)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientData)
#endif

public:
    enum Scope { CLIENT_USER_SCOPE, CLIENT_SYSTEN_SCOPE, SERVER_USER_SCOPE, SERVER_SYSTEM_SCOPE };
    inline MailData(MailDataPlugin* plugin) : Data(plugin) {}
    virtual QVariant value(const QString& key) const = 0;
    virtual void     setValue(const QString& key, const QVariant& val) = 0;
    virtual QString  part() const = 0;
    virtual quint32  owner() const = 0;
    virtual quint8   scope() const = 0;
};

#ifdef HORUS_SERVER
typedef MailData ServerMailData;
Q_DECLARE_INTERFACE(ServerMailData, "net.horus.ServerMailData/1.0");
#endif
#ifdef HORUS_CLIENT
typedef MailData ClientMailData;
Q_DECLARE_INTERFACE(ClientMailData, "net.horus.ClientMailData/1.0");
#endif

#endif // MAILDATA_H
