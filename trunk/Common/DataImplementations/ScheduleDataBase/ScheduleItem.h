#ifndef SCHEDULEITEM_H
#define SCHEDULEITEM_H

#include <QObject>
#include <QDate>

class ScheduleException
{
    public:
        inline ScheduleException(QDate ds, QDate de, QString name)
        {
            dateStart = ds;
            dateEnd = de;
            name = n;
        }
        inline ScheduleException(QDataStream& s) { *this << s; }
        inline QDataStream& operator>>(QDataStream& s) const
        {
            return s << dateStart << dateEnd << name;
        }
        inline QDataStream& operator<<(QDataStream& s)
        {
            return s >> dateStart >> dateEnd >> name;
        }
        QDate   dateStart;
        QDate   dateEnd;
        QString name;
};

class ScheduleItem
{
    public:
        inline ScheduleItem(int is, int j, QString name, QTime h, QTime he, QString d, QDate s, QDate e, bool f, int m, int t, QString c)
        {
            _idSchedule = is;
            _jWeek = j;
            _name = name;
            _hStart = h;
            _hEnd = he;
            _details = d;
            _dateStart = s;
            _dateEnd = e;
            _forceShow = f;
            _modulo = m;
            _teacher = t;
            _color = c;
        }
        inline ScheduleItem(QDataStream& s) { *this << s; }

        inline int     getIdSchedule() { return _idSchedule; }
        inline void    setIdSchedule(int is) { _idSchedule = is; }
        inline int     getJWeek() { return _jWeek; }
        inline void    setJWeek(int j) { _jWeek = j; }
        inline QString getName() { return _name; }
        inline void    setName(QString name) { _name = name; }
        inline QTime   getHStart() { return _hStart; }
        inline void    setHStart(QTime h) { _hStart = h; }
        inline QTime   getHEnd() { return _hEnd; }
        inline void    setHEnd(QTime h) { _hEnd = h; }
        inline QString getDetails() { return _details; }
        inline void    setDetails(QString d) { _details = d; }
        inline QDate   getSDate() { return _dateStart; }
        inline void    setSDate(QDate s) { _dateStart = s; }
        inline QDate   getEDate() { return _dateEnd; }
        inline void    setEDate(QDate e) { _dateEnd = e; }
        inline bool    getForce() { return _forceShow; }
        inline void    setForce(int f) { _forceShow = f; }
        inline int     getModulo() { return _modulo; }
        inline void    setModulo(bool m) { _modulo = m; }
        inline int     getTeacher() { return _teacher; }
        inline void    setTeacher(int t) { _teacher = t; }
        inline QString getColor() { return _color; }
        inline void    setColor(QString c) { _color = c; }

        inline QDataStream& operator>>(QDataStream& s) const
        { return s
          << _idSchedule
          << _jWeek
          << _name
          << _hStart
          << _hEnd
          << _details
          << _dateStart
          << _dateEnd
          << _modulo
          << _forceShow
          << _teacher
          << _color
        ;}
        inline QDataStream& operator<<(QDataStream& s)
        { return s
          >> _idSchedule
          >> _jWeek
          >> _name
          >> _hStart
          >> _hEnd
          >> _details
          >> _dateStart
          >> _dateEnd
          >> _modulo
          >> _forceShow
          >> _teacher
          >> _color
         ;}
    private:
        int     _idSchedule;
        int     _jWeek;
        QString _name;
        QTime   _hStart;
        QTime   _hEnd;
        QString _details;
        QDate   _dateStart;
        QDate   _dateEnd;
        int     _modulo;
        QList<ScheduleException *> _exception;
        bool    _forceShow;
        int     _teacher;
        QString _color;
};

#endif // SCHEDULEITEM_H
