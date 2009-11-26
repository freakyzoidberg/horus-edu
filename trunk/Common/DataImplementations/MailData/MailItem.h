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
#ifndef MAILITEM_H
#define MAILITEM_H

#include <QList>

class MailItem
{

public:
        inline MailItem(quint32 id, QStringList dest, QStringList cc, QStringList bcc, QString content)
                                                        { _id=id;   _dest=dest;    _cc=cc;  _bcc=bcc; _content=content;}

        inline MailItem(QDataStream& s) { *this << s; }

	inline int			id()     const { return _id; }
        inline QStringList			dest()   const { return _dest; }
        inline QStringList			cc()    const { return _cc; }
        inline QStringList			bcc()  const { return _bcc; }
        inline QString			content() const { return _content; }

	inline QDataStream& operator>>(QDataStream& s) const
	{ return s
	  << _id
          << _dest
          << _cc
          << _bcc
          << _content
	;}
	inline QDataStream& operator<<(QDataStream& s)
	{ return s
	  >> _id
          >> _dest
          >> _cc
          >> _bcc
          >> _content
	 ;}

private:
	quint32				_id;
        QStringList				_dest;
        QStringList				_cc;
        QStringList				_bcc;
        QString				_content;
};

typedef QList<MailItem> MailItemList;

#endif // MAILITEM_H
