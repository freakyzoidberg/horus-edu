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

#include "UserPerClass.h"

UserPerClass::UserPerClass(const QHash<quint32, UserData*>&  _users, int _id, QObject *parent)
        :  QAbstractListModel(parent), users(_users)
{
    id = _id;
}

QVariant UserPerClass::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
         return QVariant();
    //qDebug() << role << " : " << index.row();
    if (index.row() >= users.size())
         return QVariant();
    int i = 0;
    foreach (UserData* user, users)
    {
        if(user->level() == 3)
        {
            if (index.row() == i)
            {
                if (role == Qt::DisplayRole)
                    return user->login();
                else if (role == Qt::EditRole)
                    return user->login();
                else if (role == Qt::UserRole)
                    return user->id();
            }
            i++;
        }
    }
    return QVariant();
}

int UserPerClass::rowCount(const QModelIndex &parent) const
{
    quint32 i = 0;
    foreach (UserData* user, users)
        if(user->level() == 3)
        {
            if (id != -10)
            {
                if (user->studentClass()->id() == id)
                    i++;
            }
            else
                i++;
        }
    return i;
    //return users.size();
}
