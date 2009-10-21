#ifndef WHITEBOARDITEM_H
#define WHITEBOARDITEM_H

#include <QList>

class CalendarItem
{
public:
        inline CalendarItem(quint32 idLesson,    quint32 idSection, quint32 left, quint32 top, quint32 width, quint32 height,      bool isDocked)
					  { _idLesson=idLesson; _idSection=idSection;   _left=left;    _top=top;  _width=width; _height=height; _isDocked=isDocked; }

        inline CalendarItem(QDataStream& s) { *this << s; }

	inline int			idLesson()  const { return _idLesson; }
	inline int			idSection() const { return _idSection; }
	inline int			left()      const { return _left; }
	inline int			top()       const { return _top; }
	inline int			width()     const { return _width; }
	inline int			height()    const { return _height; }
	inline bool			docked()    const { return _isDocked; }

	inline QDataStream& operator>>(QDataStream& s) const
	{ return s
	  << _idLesson
	  << _idSection
	  << _left
	  << _top
	  << _width
	  << _height
	  << _isDocked
	;}
	inline QDataStream& operator<<(QDataStream& s)
	{ return s
	  >> _idLesson
	  >> _idSection
	  >> _left
	  >> _top
	  >> _width
	  >> _height
	  >> _isDocked
	 ;}

private:
	quint32				_idLesson;
	quint32				_idSection;
	quint32				_left;
	quint32				_top;
	quint32				_width;
	quint32				_height;
	bool				_isDocked;
};

typedef QList<CalendarItem> CalendarItemList;

#endif // WHITEBOARDITEM_H
