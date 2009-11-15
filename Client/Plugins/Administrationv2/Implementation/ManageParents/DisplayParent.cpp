#include		"DisplayParent.h"

#include		<QGridLayout>
#include		<QLabel>

DisplayParent::DisplayParent(QWidget *parent) : QWidget(parent)
{
	QGridLayout	*layout;
	QLabel		*fieldLabel;
	QLabel		*valueLabel;

	layout = new QGridLayout(this);
	fieldLabel = new QLabel(tr("First name"), this);
	layout->addWidget(fieldLabel, 0, 0);
	valueLabel = new QLabel("FILL ME", this);
	layout->addWidget(valueLabel, 0, 1);
	fieldLabel = new QLabel(tr("Last name"), this);
	layout->addWidget(fieldLabel, 1, 0);
	valueLabel = new QLabel("FILL ME", this);
	layout->addWidget(valueLabel, 1, 1);
	fieldLabel = new QLabel(tr("Sex"), this);
	layout->addWidget(fieldLabel, 2, 0);
	valueLabel = new QLabel("FILL ME", this);
	layout->addWidget(valueLabel, 2, 1);
	fieldLabel = new QLabel(tr("Birthday"), this);
	layout->addWidget(fieldLabel, 3, 0);
	valueLabel = new QLabel("FILL ME", this);
	layout->addWidget(valueLabel, 3, 1);
	fieldLabel = new QLabel(tr("Address"), this);
	layout->addWidget(fieldLabel, 4, 0);
	valueLabel = new QLabel("FILL ME", this);
	layout->addWidget(valueLabel, 4, 1);
	fieldLabel = new QLabel(tr("Email"), this);
	layout->addWidget(fieldLabel, 5, 0);
	valueLabel = new QLabel("FILL ME", this);
	layout->addWidget(valueLabel, 5, 1);
	fieldLabel = new QLabel(tr("Home phone"), this);
	layout->addWidget(fieldLabel, 6, 0);
	valueLabel = new QLabel("FILL ME", this);
	layout->addWidget(valueLabel, 6, 1);
	fieldLabel = new QLabel(tr("Work phone"), this);
	layout->addWidget(fieldLabel, 7, 0);
	valueLabel = new QLabel("FILL ME", this);
	layout->addWidget(valueLabel, 7, 1);
	fieldLabel = new QLabel(tr("Mobile phone"), this);
	layout->addWidget(fieldLabel, 8, 0);
	valueLabel = new QLabel("FILL ME", this);
	layout->addWidget(valueLabel, 8, 1);
	fieldLabel = new QLabel(tr("Occupational Category"), this);
	layout->addWidget(fieldLabel, 9, 0);
	valueLabel = new QLabel("FILL ME", this);
	layout->addWidget(valueLabel, 9, 1);
	fieldLabel = new QLabel(tr("Job"), this);
	layout->addWidget(fieldLabel, 10, 0);
	valueLabel = new QLabel("FILL ME", this);
	layout->addWidget(valueLabel, 10, 1);
	fieldLabel = new QLabel(tr("Type"), this);
	layout->addWidget(fieldLabel, 11, 0);
	valueLabel = new QLabel("FILL ME", this);
	layout->addWidget(valueLabel, 11, 1);
}
