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
