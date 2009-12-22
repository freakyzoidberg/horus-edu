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
#ifndef EXAMSDATABASE_H
#define EXAMSDATABASE_H

#ifdef HORUS_SERVER
    #include <QtSql>
#endif
#ifdef HORUS_CLIENT
    #include <QVariant>
#endif
#include <QByteArray>
#include <QDateTime>
#include "../../Defines.h"
#include "../../ExamsData.h"
#include "ExamsDataBasePlugin.h"

class ExamsDataBase : public ExamsData
{
	Q_OBJECT
#ifdef HORUS_SERVER
	Q_INTERFACES(ServerExamsData)
#endif
#ifdef HORUS_CLIENT
	Q_INTERFACES(ClientExamsData)
#endif

  friend class			ExamsDataBasePlugin;

	// INTERFACE ExamsData
public:
	 inline QString		comment() { return _comment; }
	 inline void		setComment(const QString& comment) { _comment = comment; }

	 inline void		setDate(const QDate& date) { _date = date; }
	 inline QDate		date() { return _date; }


	 inline quint32		teacher() const { return _teacher; }
	 inline void		setTeacher(const quint32 id) { _teacher = id; }

	 inline TreeData*	subject() const { return _subject; }
	 void				setSubject(TreeData* node) { _subject = node; }

	inline ExamsData*	exam() const	{ return _exam; }
	void				setExam(ExamsData* exam) { _exam = exam; }

	//INTERFACE Data
public:
	void				keyToStream(QDataStream& s) const;
	void				dataToStream(QDataStream& s) const;
	void				dataFromStream(QDataStream& s);

	bool				canChange(UserData* user) const;
	bool				canAccess(UserData* user) const;

	const QList<Data*>	dependsOfCreatedData() const;

	QDebug				operator<<(QDebug debug) const;

#ifdef HORUS_CLIENT
	QVariant			data(int column, int role = Qt::DisplayRole) const;
#endif
#ifdef HORUS_SERVER
public:
	quint8				serverRead();
	quint8				serverCreate();
	quint8				serverSave();
	quint8				serverRemove();
#endif

private:
	ExamsDataBase(quint32 id, ExamsDataBasePlugin* plugin);
	~ExamsDataBase() {}

	QString				_comment;
	QDate				_date;
	TreeData*			_subject;
	quint32				_teacher;
	ExamsData			*_exam;

};

#endif // EXAMSDATABASE_H
