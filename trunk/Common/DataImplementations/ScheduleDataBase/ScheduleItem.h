#ifndef SCHEDULEITEM_H
#define SCHEDULEITEM_H

#include <QObject>
#include <QDate>

struct ScheduleException
{
    QDate   dateStart;
    QDate   dateEnd;
};

class ScheduleItem : public QObject
{
    public:
        ScheduleItem();
        int     getId() { return _id; }
        void    setId(int id) { _id = id; }
        int     getIdSchedule() { return _idSchedule; }
        void    setIdSchedule(int is) { _idSchedule = is; }
        int     getJWeek() { return _jWeek; }
        void    setJWeek(int j) { _jWeek = j; }
        QString getName() { return _name; }
        void    setName(QString name) { _name = name; }
        QTime   getHStart() { return _hStart; }
        void    setHStart(QTime h) { _hStart = h; }
        QTime   getHEnd() { return _hEnd; }
        void    setHEnd(QTime h) { _hEnd = h; }
        QString getDetails() { return _details; }
        void    setDetails(QString d) { _details = d; }
        QDate   getSDate() { return _dateStart; }
        void    setSDate(QDate s) { _dateStart = s; }
        QDate   getEDate() { return _dateEnd; }
        void    setEDate(QDate e) { _dateEnd = e; }
        bool    getForce() { return _forceShow; }
        void    setForce(int f) { _forceShow = f; }
        int     getModulo() { return _modulo; }
        void    setModulo(bool m) { _modulo = m; }
        int     getTeacher() { return _teacher; }
        void    setTeacher(int t) { _teacher = t; }
    private:
        int     _id;
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

};

#endif // SCHEDULEITEM_H
