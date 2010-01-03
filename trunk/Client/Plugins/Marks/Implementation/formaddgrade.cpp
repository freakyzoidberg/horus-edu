#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QVariant>
#include <QTextEdit>

#include "formaddgrade.h"

FormAddGrade::FormAddGrade()
{
	QGridLayout	*mainLayout = new QGridLayout(this);
	QLabel		*commentLabel = new QLabel(tr("Commentaire:"));
	QTextEdit	*commentEdit = new QTextEdit();
	QLabel		*markLabel = new QLabel(tr("Note:"));
	QLineEdit	*markEdit = new QLineEdit();
	QLabel *title = new QLabel(tr("Ajout d'une note."), this);
	title->setProperty("isFormTitle", QVariant(true));
	title->setMaximumHeight(30);

	mainLayout->addWidget(title, 0, 0, 1, 2);
	mainLayout->addWidget(commentLabel, 1, 0, 1, 2);
	mainLayout->addWidget(commentEdit, 2, 0, 2, 2);
	mainLayout->addWidget(markLabel,4, 0);
	mainLayout->addWidget(markEdit, 4, 1);
	mainLayout->addWidget(new QWidget(), 5, 0, 10, 2);
}
