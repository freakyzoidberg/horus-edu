#include "newexams.h"

#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>

NewExams::NewExams()
{
	mainLayout = new QVBoxLayout(this);
   mainLayout->setSpacing(0);
		mainLayout->setMargin(0);

	//QLabel *title = new QLabel(tr("Dates de l\'emploi du temps"), this);
	/* FIX FOR V1 */
	QLabel *title = new QLabel(tr("Creation d'un examen."), this);
	/* END FIX FOR v1 */
	title->setProperty("isFormTitle", true);
	title->setMaximumHeight(30);
	mainLayout->addWidget(title);

//classListView->setMaximumHeight(64);
	QFrame *eventFrame = new QFrame();
	eventFrame->setProperty("isFormFrame", true);
	QBoxLayout *eventMainLayout = new QBoxLayout(QBoxLayout::TopToBottom, eventFrame);
	eventMainLayout->setSpacing(0);
	eventMainLayout->setMargin(0);

	QLabel *startlabel = new QLabel(tr("Date :"));
	startlabel->setMaximumHeight(30);
	startlabel->setProperty("isFormLabel", true);
	//datesLayout->addWidget(startlabel, 1, 0);

	thedate = new QDateEdit();

	examComment = new QLineEdit();
	mainLayout->addWidget(startlabel);
	mainLayout->addWidget(thedate);

	QLabel *thecomment = new QLabel(tr("Title :"));
	thecomment->setMaximumHeight(30);
	thecomment->setProperty("isFormLabel", true);
	mainLayout->addWidget(thecomment);
	mainLayout->addWidget(examComment);
	mainLayout->addWidget(new QWidget());

}
