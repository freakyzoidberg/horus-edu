
#include "formaddgrade.h"

FormAddGrade::FormAddGrade()
{
	_mainLayout = new QGridLayout(this);
	_commentLabel = new QLabel(tr("Commentaire:"));
	_commentEdit = new QTextEdit();
	_markLabel = new QLabel(tr("Note:"));
	_markEdit = new QLineEdit();
	QLabel *title = new QLabel(tr("Ajout d'une note."), this);
	title->setProperty("isFormTitle", QVariant(true));
	title->setMaximumHeight(30);

	_mainLayout->addWidget(title, 0, 0, 1, 2);
	_mainLayout->addWidget(_commentLabel, 1, 0, 1, 2);
	_mainLayout->addWidget(_commentEdit, 2, 0, 2, 2);
	_mainLayout->addWidget(_markLabel,4, 0);
	_mainLayout->addWidget(_markEdit, 4, 1);
	_mainLayout->addWidget(new QWidget(), 5, 0, 10, 2);
}
