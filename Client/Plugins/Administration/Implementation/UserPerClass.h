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
#ifndef USERPERCLASS_H
#define USERPERCLASS_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include "../../../../Common/UserData.h"
#include "../../../../Common/TreeData.h"

class UserPerClass : public QAbstractListModel
{
    Q_OBJECT

    public:
     UserPerClass(const QHash<quint32, UserData*>& users, int _id, QObject *parent = 0);

     QVariant data(const QModelIndex &index, int role) const;
//     QVariant headerData(int section, Qt::Orientation orientation,
//                         int role = Qt::DisplayRole) const;
//     QModelIndex index(int row, int column,
//                       const QModelIndex &parent = QModelIndex()) const;
//     QModelIndex parent(const QModelIndex &index) const;
//     int columnCount(const QModelIndex &parent = QModelIndex()) const;
     int rowCount(const QModelIndex &parent = QModelIndex()) const;


private:
     const QHash<quint32,UserData*>& users;
     quint32                         id;
};


#endif // USERPERCLASS_H
