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
    void keyToStream(QDataStream& s);
    void dataToStream(QDataStream& s) const;
    void dataFromStream(QDataStream& s);
    QDebug operator<<(QDebug debug) const;
#ifdef HORUS_CLIENT
    QVariant data(int column, int role = Qt::DisplayRole) const;
#endif
#ifdef HORUS_SERVER
        inline quint8     serverRead()   { return NONE; }
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
public :
        inline void			setId(QString i)     { _id = i; }
        inline void			setFrom(QString i)     { _from = i; }
        inline void			setMDate(QString i)     { _date = i; }
        inline void			setTo(QStringList t) { _to = t; }
        inline void			setCc(QStringList c)     { _cc = c; }
        inline void                     setBcc(QStringList b)   { _bcc = b; }
        inline void			setContent(QString Con) { _content = Con; }
        inline void                     setSubject(QString Sub) {_subject = Sub; }
        inline void                     sendMail() { Data::setStatus(SAVING); }

        inline QString			getContent() const { return _content; }
         inline QString                    getSubject() {return _subject; }
         inline QString                    getMDate() {return _date; }
         inline QString                    getFrom() {return _from; }


};

#endif // MAILDATA_H
