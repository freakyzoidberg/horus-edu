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
#include					"StructureForm.h"

#include					<QSortFilterProxyModel>
#include					<QGridLayout>
#include					<QBoxLayout>
#include					<QPushButton>

StructureForm::StructureForm(QWidget *parent, UserDataPlugin *userDataPlugin) : QWidget(parent), _userDataPlugin(userDataPlugin)
{
	QFrame					*formFrame;
	QGridLayout				*leftLayout;
	QBoxLayout				*mainLayout;
	QBoxLayout				*formLayout;
	QBoxLayout				*actionsLayout;
	QLabel					*actionsTitle;
	QPushButton				*okButton;
	QPushButton				*cancelButton;
	QLabel					*label;
	QSortFilterProxyModel	*teachers;

	mainLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
	formFrame = new QFrame();
	mainLayout->addWidget(formFrame);
	formFrame->setProperty("isFormFrame", true);
	formLayout = new QBoxLayout(QBoxLayout::LeftToRight, formFrame);
	formLayout->setSpacing(0);
	formLayout->setMargin(0);
	leftLayout = new QGridLayout();
	formLayout->addLayout(leftLayout);
	leftLayout->setSpacing(4);
	leftLayout->setMargin(8);
	leftLayout->setColumnMinimumWidth(0, 150);
	titleLabel = new QLabel(formFrame);
	titleLabel->setProperty("isFormTitle", true);
	leftLayout->addWidget(titleLabel, 0, 0, 1, 2);
	label = new QLabel(tr("Name"), formFrame);
	label->setProperty("isFormLabel", true);
	leftLayout->addWidget(label, 1, 0);
	nameField = new QLineEdit(formFrame);
	leftLayout->addWidget(nameField, 1, 1);
	teacherField = new QComboBox(formFrame);
	teachers = new QSortFilterProxyModel(this);
	teachers->setSourceModel(userDataPlugin->listModel());
	teachers->setFilterRole(Data::FILTER_ROLE);
	teachers->setFilterKeyColumn(0);
	teachers->setFilterFixedString("TEACHER");
	teachers->setDynamicSortFilter(true);
	teacherField->setModel(teachers);
	teacherField->setModelColumn(1);
	teacherLabel = new QLabel(tr("Teacher"), formFrame);
	teacherLabel->setProperty("isFormLabel", true);
	leftLayout->addWidget(teacherLabel, 2, 0);
	leftLayout->addWidget(teacherField, 2, 1);
	actionsLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	mainLayout->addLayout(actionsLayout);
	actionsTitle = new QLabel(tr("Actions:"), this);
    actionsTitle->setProperty("isTitle", true);
    actionsTitle->setProperty("isRound", true);
	actionsLayout->addWidget(actionsTitle);
	okButton = new QPushButton(QIcon(":/Icons/ok.png"), tr("Ok"), this);
	cancelButton = new QPushButton(QIcon(":/Icons/reset.png"), tr("Cancel"), this);
	actionsLayout->addWidget(okButton);
	actionsLayout->addWidget(cancelButton);
	actionsLayout->addWidget(new QWidget(this), 1);
	connect(okButton, SIGNAL(clicked()), this, SLOT(validate()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
}

QString						StructureForm::getName() const
{
	return (nameField->text());
}

UserData					*StructureForm::getTeacher() const
{
	if (teacherField->currentIndex() < 0)
		return (_userDataPlugin->nobody());
	return (_userDataPlugin->user(teacherField->itemData(teacherField->currentIndex(), Qt::DisplayRole).toString()));
}

void						StructureForm::setTitle(QString title)
{
	titleLabel->setText(title);
}

void						StructureForm::setName(QString name)
{
	nameField->setText(name);
}

void						StructureForm::setTeacher(UserData *teacher)
{
	if (teacher)
		teacherField->setCurrentIndex(teacherField->findData(teacher->data(1), Qt::DisplayRole));
	else
		teacherField->setCurrentIndex(-1);
}

void						StructureForm::setTeacherVisibility(bool hidden)
{
	if (hidden)
	{
		teacherField->hide();
		teacherLabel->hide();
	}
	else
	{
		teacherField->show();
		teacherLabel->show();
	}
}

void						StructureForm::validate()
{
	this->hide();
	emit validated();
}

void						StructureForm::cancel()
{
	this->hide();
	emit canceled();
}
