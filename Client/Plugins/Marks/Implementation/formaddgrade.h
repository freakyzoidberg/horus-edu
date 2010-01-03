#ifndef FORMADDGRADE_H
#define FORMADDGRADE_H

#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QVariant>
#include <QTextEdit>

class FormAddGrade : public QWidget
{
public:
    FormAddGrade();
	QGridLayout		*mainLayout()	{ return _mainLayout; }
	QLabel			*commentLabel() { return _commentLabel; }
	QTextEdit		*commentEdit()	{ return _commentEdit; }
	QLabel			*markLabel()	{ return _markLabel; }
	QLineEdit		*markEdit()		{ return _markEdit; }

private:
	QGridLayout		*_mainLayout;
	QLabel			*_commentLabel;
	QTextEdit		*_commentEdit;
	QLabel			*_markLabel;
	QLineEdit		*_markEdit;
};

#endif // FORMADDGRADE_H
