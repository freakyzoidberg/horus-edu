#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>

#include "formaddgrade.h"

FormAddGrade::FormAddGrade()
{
	QGridLayout	*mainLayout = new QGridLayout(this);
	QLabel		*commentLabel = new QLabel(tr("Commentaire:"));
	QLineEdit	*commentEdit = new QLineEdit();
	QLabel		*markLabel = new QLabel(tr("Note:"));
	QLineEdit	*markEdit = new QLineEdit();

	mainLayout->addWidget(commentLabel, 0, 0);
	mainLayout->addWidget(commentEdit, 0, 1);
	mainLayout->addWidget(markLabel,1, 0);
	mainLayout->addWidget(markEdit, 1, 1);
	mainLayout->addWidget(new QWidget(), 2, 0, 10, 2);
}
