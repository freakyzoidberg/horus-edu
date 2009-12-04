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
#ifndef MARKSDATABASE_H
#define MARKSDATABASE_H

#ifdef HORUS_SERVER
    #include <QtSql>
#endif
#ifdef HORUS_CLIENT
    #include <QVariant>
#endif
#include <QByteArray>
#include <QDateTime>
#include "../../Defines.h"
#include "../../MarksData.h"
#include "MarksDataBasePlugin.h"

class MarksDataBase : public MarksData
{
	Q_OBJECT
#ifdef HORUS_SERVER
        Q_INTERFACES(ServerMarksData)
#endif
#ifdef HORUS_CLIENT
        Q_INTERFACES(ClientMarksData)
#endif

  friend class			MarksDataBasePlugin;

private:
                                                MarksDataBase(MarksDataBasePlugin* plugin);
        inline				~MarksDataBase() {}


        int                             _id;
        int                             _idUser;
        int                             _idEvent;
        QVariant                        _mark;
        QVariant                        _quote;
        QDateTime                       _date;


        // INTERFACE AttendanceData
public:
        inline int                      id() const { return _id; }
        inline QDateTime		date() const { return _date; }
        inline void			setDate(const QDateTime& date) { _date = date; }
        inline int                      idUser() const { return _idUser; }
        inline void			setIdUser(const int user) {_idUser = user; }
        inline int                      idEvent() const { return _idEvent; }
        inline void			setIdEvent(const int event) { _idEvent = event; }
        //inline void                     setmark(const QVariant note) { _mark = mark; }
        inline QVariant                 mark() const { return _mark; }
        inline void                     setQuote(const QVariant quote) { _quote = quote; }
        inline QVariant                 quote() const { return _quote; }

	//INTERFACE Data
public:
	void				keyToStream(QDataStream& s);
	void				dataToStream(QDataStream& s) const;
	void				dataFromStream(QDataStream& s);

	QDebug				operator<<(QDebug debug) const;

#ifdef HORUS_CLIENT
	QVariant			data(int column, int role = Qt::DisplayRole) const;
public slots:
	void				create();
#endif
#ifdef HORUS_SERVER
public:
	quint8				serverRead();
	quint8				serverCreate();
	quint8				serverSave();
	quint8				serverRemove();
#endif
};

#endif // MARKSDATABASE_H
