#ifndef CLASSLIST_H
#define CLASSLIST_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>

class ClassListClass : public QWidget
{
	Q_OBJECT

public:
    ClassListClass();
	QVBoxLayout		*listLayout()	{ return _listLayout; }
	QListWidget		*classList()	{ return _classList; }

private:
	QVBoxLayout		*_listLayout;
	QListWidget		*_classList;
};

#endif // CLASSLIST_H
