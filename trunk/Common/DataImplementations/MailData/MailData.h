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

#ifdef HORUS_SERVER
    #include <QtSql>
#endif
#ifdef HORUS_CLIENT
    #include <QVariant>
#endif
#include <QByteArray>
#include <QDateTime>
#include "../../Data.h"
#include "MailDataPlugin.h"
#include "../../UserData.h"

class UserData;
class MailData : public Data
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerData)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientData)
#endif

  friend class MailDataPlugin;

public:
    // Data Interface
	void keyToStream(QDataStream& s) const;
    void dataToStream(QDataStream& s) const;
    void dataFromStream(QDataStream& s);
    QDebug operator<<(QDebug debug) const;
#ifdef HORUS_CLIENT
    QVariant data(int column, int role = Qt::DisplayRole) const;
#endif
#ifdef HORUS_SERVER
	inline quint8     serverCreate() { return INTERNAL_SERVER_ERROR; }
               quint8     serverSave();
	inline quint8     serverRemove() { return INTERNAL_SERVER_ERROR; }
#endif

/*
	inline TreeData*			node() const { return _node;  }
        inline MailItemList&	items() { return _items; }
*/
private:
    inline MailData(MailDataPlugin* plugin) : Data(plugin) {}
    inline ~MailData() {}

private:
        QString				_id;
        QStringList			_to;
        QStringList			_cc;
        QStringList                     _bcc;
        QString				_content;
        QString                         _subject;
        QString                         _date;
        QString                         _from;
        QString                         _box;
public :
        inline void			setId(QString i)     { _id = i; }
        inline void			setFrom(QString i)     { _from = i; }
        inline void			setBox(QString i)     { _box = i; }
        inline void			setMDate(QString i)     { _date = i; }
        inline void			setTo(QStringList t) { _to = t; }
        inline void			setCc(QStringList c)     { _cc = c; }
        inline void                     setBcc(QStringList b)   { _bcc = b; }
        inline void			setContent(QString Con) { _content = Con; }
        inline void                     setSubject(QString Sub) {_subject = Sub; }
		inline void                     sendMail() { Data::save(); }

        inline QString			getContent() const { return _content; }
         inline QString                    getSubject() {return _subject; }
         inline QString                    getMDate() {return _date; }
         inline QString                    getFrom() {return _from; }
         inline QString                    getId() {return _id; }
         inline QStringList                    getCc() {return _cc; }
         inline QString                    getBox() {return _box; }


};

#endif // MAILDATA_H
