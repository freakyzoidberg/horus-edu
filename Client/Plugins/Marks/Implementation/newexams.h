#ifndef NEWEXAMS_H
#define NEWEXAMS_H

#include <QWidget>
#include <QDateEdit>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLineEdit>

class NewExams : public QWidget
{
public:
	NewExams(QVBoxLayout *RightLayout);
	QDateEdit *thedate;
	QLineEdit *examComment;

private:
	 QDateEdit                   *_startDate;
		QDateEdit                   *_endDate;
		QVBoxLayout                  *mainLayout;
		QGridLayout                 *datesLayout;
		QGridLayout                 *exceptionLayout;
};

#endif // NEWEXAMS_H
