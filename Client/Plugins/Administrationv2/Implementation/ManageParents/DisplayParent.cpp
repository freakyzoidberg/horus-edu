#include		"DisplayParent.h"

#include		<QGridLayout>
#include		<QLabel>

DisplayParent::DisplayParent(QWidget *parent) : QWidget(parent)
{
}

DisplayParent::DisplayParent(QWidget *parent, UserData *user) : QWidget(parent)
{
	QGridLayout	*layout;
	QLabel		*fieldLabel;
	QLabel		*valueLabel;
	QString		value;
	int			row;

	row = 0;
	layout = new QGridLayout(this);
	value = user->surname();
	if (value.size())
	{
		fieldLabel = new QLabel(tr("First name"), this);
		layout->addWidget(fieldLabel, row, 0);
		valueLabel = new QLabel(value, this);
		layout->addWidget(valueLabel, row, 1);
		++row;
	}
	value = user->name();
	if (value.size())
	{
		fieldLabel = new QLabel(tr("Last name"), this);
		layout->addWidget(fieldLabel, row, 0);
		valueLabel = new QLabel(value, this);
		layout->addWidget(valueLabel, row, 1);
		++row;
	}
	value = user->gender();
	if (value.size())
	{
		fieldLabel = new QLabel(tr("Gender"), this);
		layout->addWidget(fieldLabel, row, 0);
		valueLabel = new QLabel(value, this);
		layout->addWidget(valueLabel, row, 1);
		++row;
	}
	value = user->birthDate().toString();
	if (value.size())
	{
		fieldLabel = new QLabel(tr("Birth date"), this);
		layout->addWidget(fieldLabel, row, 0);
		valueLabel = new QLabel(value, this);
		layout->addWidget(valueLabel, row, 1);
		++row;
	}
	value = user->address();
	if (value.size())
	{
		fieldLabel = new QLabel(tr("Address"), this);
		layout->addWidget(fieldLabel, row, 0);
		valueLabel = new QLabel(value, this);
		layout->addWidget(valueLabel, row, 1);
		++row;
	}
	value = user->mail();
	if (value.size())
	{
		fieldLabel = new QLabel(tr("Email"), this);
		layout->addWidget(fieldLabel, row, 0);
		valueLabel = new QLabel(value, this);
		layout->addWidget(valueLabel, row, 1);
		++row;
	}
	value = user->phone1();
	if (value.size())
	{
		fieldLabel = new QLabel(tr("Home phone"), this);
		layout->addWidget(fieldLabel, row, 0);
		valueLabel = new QLabel(value, this);
		layout->addWidget(valueLabel, row, 1);
		++row;
	}
	value = user->phone2();
	if (value.size())
	{
		fieldLabel = new QLabel(tr("Work phone"), this);
		layout->addWidget(fieldLabel, row, 0);
		valueLabel = new QLabel(value, this);
		layout->addWidget(valueLabel, row, 1);
		++row;
	}
	value = user->phone3();
	if (value.size())
	{
		fieldLabel = new QLabel(tr("Mobile phone"), this);
		layout->addWidget(fieldLabel, row, 0);
		valueLabel = new QLabel(value, this);
		layout->addWidget(valueLabel, row, 1);
		++row;
	}
	value = user->proCategory();
	if (value.size())
	{
		fieldLabel = new QLabel(tr("Occupational category"), this);
		layout->addWidget(fieldLabel, row, 0);
		valueLabel = new QLabel(value, this);
		layout->addWidget(valueLabel, row, 1);
		++row;
	}
	value = user->occupation();
	if (value.size())
	{
		fieldLabel = new QLabel(tr("Occupation"), this);
		layout->addWidget(fieldLabel, row, 0);
		valueLabel = new QLabel(value, this);
		layout->addWidget(valueLabel, row, 1);
		++row;
	}
	value = user->relationship();
	if (value.size())
	{
		fieldLabel = new QLabel(tr("Relationship"), this);
		layout->addWidget(fieldLabel, row, 0);
		valueLabel = new QLabel(value, this);
		layout->addWidget(valueLabel, row, 1);
		++row;
	}
}
