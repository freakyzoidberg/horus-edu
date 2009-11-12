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
        inline void                     setmark(const QVariant note) { _mark = mark; }
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
