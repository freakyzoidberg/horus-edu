#ifndef CLASSLIST_H
#define CLASSLIST_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>

class ClassList : public QWidget
{
public:
    ClassList();
	QVBoxLayout		*listLayout()	{ return _listLayout; }
	QListWidget		*classList()	{ return _classList; }

private:
	QVBoxLayout		*_listLayout;
	QListWidget		*_classList;
};

#endif // CLASSLIST_H
