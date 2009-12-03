/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
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

	if (!user)
		return ;
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
	if (user->gender() == GENDER_UNKNOW)
		value = tr("Unknow");
	if (user->gender() == GENDER_FEMALE)
		value = tr("Female");
	if (user->gender() == GENDER_MALE)
		value = tr("Male");
	if (value.size())
	{
		fieldLabel = new QLabel(tr("Gender"), this);
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
