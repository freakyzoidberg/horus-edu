#ifndef MAILITEM_H
#define MAILITEM_H

#include <QList>

class MailItem
{
public:
        inline MailItem(quint32 id, quint32 left, quint32 top, quint32 width, quint32 height,      bool isDocked)
							{ _id=id;   _left=left;    _top=top;  _width=width; _height=height; _isDocked=isDocked; }

        inline MailItem(QDataStream& s) { *this << s; }

	inline int			id()     const { return _id; }
	inline int			left()   const { return _left; }
	inline int			top()    const { return _top; }
	inline int			width()  const { return _width; }
	inline int			height() const { return _height; }
	inline bool			docked() const { return _isDocked; }

	inline QDataStream& operator>>(QDataStream& s) const
	{ return s
	  << _id
	  << _left
	  << _top
	  << _width
	  << _height
	  << _isDocked
	;}
	inline QDataStream& operator<<(QDataStream& s)
	{ return s
	  >> _id
	  >> _left
	  >> _top
	  >> _width
	  >> _height
	  >> _isDocked
	 ;}

private:
	quint32				_id;
	quint32				_left;
	quint32				_top;
	quint32				_width;
	quint32				_height;
	bool				_isDocked;
};

typedef QList<MailItem> MailItemList;

#endif // MAILITEM_H
