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
#include "../../ExamsData.h"

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
	MarksDataBase(TreeData* node, MarksDataBasePlugin* plugin);
	~MarksDataBase() {}

	QString			_result;
	QString			_comment;
	QDate			_date;
	ExamsData*		_exam;
	quint32			_student;

	// INTERFACE MarksData
public:
	inline QString	              result() const  { return _result; }
	inline void       setResult(const QString& result)  { _result = result; }

	 inline QString	comment() { return _comment; }
	 inline void	setComment(const QString& comment) { _comment = comment; }

	 inline void           setDate(const QDate& date) { _date = date; }
	 inline QDate			date() { return _date; }

	 inline ExamsData*               exam() const { return _exam; }
		inline	void		setExam(ExamsData *exam) { _exam = exam; }

	inline void			setStudent(const quint32 id) { _student = id; }
	inline quint32		student() const { return _student; }




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
};

#endif // MARKSDATABASE_H
