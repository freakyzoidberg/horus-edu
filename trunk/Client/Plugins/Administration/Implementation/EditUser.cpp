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
#include		"EditUser.h"

#include		<QGridLayout>
#include		<QBoxLayout>
#include		<QFrame>
#include		<QPushButton>
#include		<QScrollArea>
#include		<QCompleter>

EditUser::EditUser(QWidget *parent, UserDataPlugin *userDataPlugin, int userLevel, TreeData *node, UserData *user) : QWidget(parent), _userDataPlugin(userDataPlugin), _userLevel(userLevel), _node(node), _user(user)
{
	QBoxLayout	*mainLayout;
	QBoxLayout	*leftLayout;
	QBoxLayout	*rightLayout;
	QBoxLayout	*informationsLayout;
	QScrollArea	*scrollArea;
	QFrame		*informationsFrame;
	QLabel		*informationsTitle;
	QLabel		*actionsTitle;
	QPushButton	*applyButton;
	QPushButton	*okButton;
	QPushButton	*resetButton;
	QPushButton	*cancelButton;
	QWidget		*scrollWidget;

	father = 0;
	mother = 0;
	mainLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
	mainLayout->setSpacing(0);
	mainLayout->setMargin(2);
	scrollArea = new QScrollArea(this);
	scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea->setWidgetResizable(true);
	scrollWidget = new QWidget(this);
	leftLayout = new QBoxLayout(QBoxLayout::TopToBottom, scrollWidget);
	leftLayout->setSpacing(0);
	leftLayout->setMargin(0);
	leftLayout->addWidget(getPersonnalFrame());
	leftLayout->addWidget(getContactFrame());
	if (userLevel != LEVEL_STUDENT)
		leftLayout->addWidget(getProfessionalFrame());
	else
	{
		leftLayout->addWidget(getStudiesFrame());
		leftLayout->addWidget(getParentFrame());
		leftLayout->addWidget(getParentContactFrame());
	}
	leftLayout->addWidget(new QWidget(scrollWidget), 1);
	scrollArea->setWidget(scrollWidget);
	mainLayout->addWidget(scrollArea);
	rightLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	rightLayout->setMargin(0);
	rightLayout->setSpacing(2);
	informationsFrame = new QFrame(this);
	informationsLayout = new QBoxLayout(QBoxLayout::TopToBottom, informationsFrame);
	informationsLayout->setSpacing(0);
	informationsLayout->setMargin(0);
	informationsFrame->setMinimumWidth(200);
	informationsTitle = new QLabel(tr("Informations:"), informationsFrame);
	informationsTitle->setProperty("isTitle", true);
	informationsTitle->setProperty("isRound", true);
	informationsLayout->addWidget(informationsTitle);
	rightLayout->addWidget(informationsFrame);
	actionsTitle = new QLabel(tr("Actions:"), this);
	actionsTitle->setProperty("isTitle", true);
	actionsTitle->setProperty("isRound", true);
	rightLayout->addWidget(actionsTitle);
	okButton = new QPushButton(QIcon(":/Icons/ok.png"), tr("OK"), this);
	rightLayout->addWidget(okButton);
	applyButton = new QPushButton(QIcon(":/Icons/save.png"), tr("Apply"), this);
	rightLayout->addWidget(applyButton);
	resetButton = new QPushButton(QIcon(":/Icons/reset.png"), tr("Reset"), this);
	rightLayout->addWidget(resetButton);
	cancelButton = new QPushButton(QIcon(":/Icons/back.png"), tr("Cancel"), this);
	rightLayout->addWidget(cancelButton);
	rightLayout->addWidget(new QWidget(this), 1);
	mainLayout->addLayout(rightLayout);
	connect(okButton, SIGNAL(clicked()), this, SLOT(saved()));
	connect(applyButton, SIGNAL(clicked()), this, SLOT(applied()));
	connect(resetButton, SIGNAL(clicked()), this, SLOT(reseted()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(exited()));
}

QWidget			*EditUser::getPersonnalFrame()
{
	QFrame		*personnalFrame;
	QGridLayout	*personnalBottomLayout;
	QBoxLayout	*personnalMainLayout;
	QLabel		*personnalTitle;
	QLabel		*label;
	QCompleter	*completer;

	personnalFrame = new QFrame();
	personnalFrame->setProperty("isFormFrame", true);
	personnalMainLayout = new QBoxLayout(QBoxLayout::TopToBottom, personnalFrame);
	personnalMainLayout->setSpacing(0);
	personnalMainLayout->setMargin(0);
	personnalTitle = new QLabel(tr("Personnal informations"), personnalFrame);
	personnalTitle->setProperty("isFormTitle", true);
	personnalMainLayout->addWidget(personnalTitle);
	personnalBottomLayout = new QGridLayout();
	personnalBottomLayout->setSpacing(4);
	personnalBottomLayout->setMargin(8);
	personnalBottomLayout->setColumnMinimumWidth(0, 150);
	label = new QLabel(tr("Last name"), personnalFrame);
	label->setProperty("isFormLabel", true);
	personnalBottomLayout->addWidget(label, 0, 0);
	lastNameField = new QLineEdit(personnalFrame);
	completer = new QCompleter(_userDataPlugin->listModel(), this);
	completer->setCompletionColumn(2);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	lastNameField->setCompleter(completer);
	personnalBottomLayout->addWidget(lastNameField, 0, 1);
	label = new QLabel(tr("First name"), personnalFrame);
	label->setProperty("isFormLabel", true);
	personnalBottomLayout->addWidget(label, 0, 2);
	firstNameField = new QLineEdit(personnalFrame);
	completer = new QCompleter(_userDataPlugin->listModel(), this);
	completer->setCompletionColumn(3);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	firstNameField->setCompleter(completer);
	personnalBottomLayout->addWidget(firstNameField, 0, 3);
	label = new QLabel(tr("Birth date"), personnalFrame);
	label->setProperty("isFormLabel", true);
	personnalBottomLayout->addWidget(label, 1, 0);
	birthDateField = new QDateEdit(personnalFrame);
	birthDateField->setDate(QDate::currentDate());
	birthDateField->setCalendarPopup(true);
	birthDateField->setDisplayFormat(tr("dd/MM/yy"));
	personnalBottomLayout->addWidget(birthDateField, 1, 1);
	label = new QLabel(tr("Birth place"), personnalFrame);
	label->setProperty("isFormLabel", true);
	personnalBottomLayout->addWidget(label, 1, 2);
	birthPlaceField = new QLineEdit(personnalFrame);
	completer = new QCompleter(_userDataPlugin->listModel(), this);
	completer->setCompletionColumn(4);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	birthPlaceField->setCompleter(completer);
	personnalBottomLayout->addWidget(birthPlaceField, 1, 3);
	label = new QLabel(tr("Gender"), personnalFrame);
	label->setProperty("isFormLabel", true);
	personnalBottomLayout->addWidget(label, 2, 0);
	genderField = new QComboBox(personnalFrame);
	genderField->addItem(tr("Unknow"), GENDER_UNKNOW);
	genderField->addItem(tr("Female"), GENDER_FEMALE);
	genderField->addItem(tr("Male"), GENDER_MALE);
	if (_userLevel != LEVEL_STUDENT)
		personnalBottomLayout->addWidget(genderField, 2, 1, 1, 3);
	else
	{
		personnalBottomLayout->addWidget(genderField, 2, 1);
		label = new QLabel(tr("Siblings"), personnalFrame);
		label->setProperty("isFormLabel", true);
		personnalBottomLayout->addWidget(label, 2, 2);
		siblingsField = new QSpinBox(personnalFrame);
		personnalBottomLayout->addWidget(siblingsField, 2, 3);
	}
	personnalMainLayout->addLayout(personnalBottomLayout);
	if (_user)
	{
		firstNameField->setText(_user->surname());
		lastNameField->setText(_user->name());
		birthDateField->setDate(_user->birthDate());
		birthPlaceField->setText(_user->bornPlace());
		genderField->setCurrentIndex(genderField->findData(_user->gender()));
		if (_userLevel == LEVEL_STUDENT)
			siblingsField->setValue(_user->nbrBrothers());
	}
	return (personnalFrame);
}

QWidget			*EditUser::getContactFrame()
{
	QFrame		*contactFrame;
	QGridLayout	*contactBottomLayout;
	QBoxLayout	*contactMainLayout;
	QLabel		*contactTitle;
	QLabel		*label;
	QCompleter	*completer;

	contactFrame = new QFrame();
	contactFrame->setProperty("isFormFrame", true);
	contactMainLayout = new QBoxLayout(QBoxLayout::TopToBottom, contactFrame);
	contactMainLayout->setSpacing(0);
	contactMainLayout->setMargin(0);
	contactTitle = new QLabel(tr("Contact informations"), contactFrame);
	contactTitle->setProperty("isFormTitle", true);
	contactMainLayout->addWidget(contactTitle);
	contactBottomLayout = new QGridLayout();
	contactBottomLayout->setSpacing(4);
	contactBottomLayout->setMargin(8);
	contactBottomLayout->setColumnMinimumWidth(0, 150);
	label = new QLabel(tr("Address"), contactFrame);
	label->setProperty("isFormLabel", true);
	contactBottomLayout->addWidget(label, 0, 0);
	addressField = new QTextEdit(contactFrame);
	contactBottomLayout->addWidget(addressField, 0, 1);
	label = new QLabel(tr("Email"), contactFrame);
	label->setProperty("isFormLabel", true);
	contactBottomLayout->addWidget(label, 1, 0);
	mailField = new QLineEdit(contactFrame);
	completer = new QCompleter(_userDataPlugin->listModel(), this);
	completer->setCompletionColumn(5);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	mailField->setCompleter(completer);
	contactBottomLayout->addWidget(mailField, 1, 1);
	label = new QLabel(tr("Home phone"), contactFrame);
	label->setProperty("isFormLabel", true);
	contactBottomLayout->addWidget(label, 2, 0);
	homePhoneField = new QLineEdit(contactFrame);
	completer = new QCompleter(_userDataPlugin->listModel(), this);
	completer->setCompletionColumn(6);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	homePhoneField->setCompleter(completer);
	contactBottomLayout->addWidget(homePhoneField, 2, 1);
	label = new QLabel(tr("Mobile phone"), contactFrame);
	label->setProperty("isFormLabel", true);
	contactBottomLayout->addWidget(label, 3, 0);
	mobilePhoneField = new QLineEdit(contactFrame);
	completer = new QCompleter(_userDataPlugin->listModel(), this);
	completer->setCompletionColumn(7);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	mobilePhoneField->setCompleter(completer);
	contactBottomLayout->addWidget(mobilePhoneField, 3, 1);
	if (_userLevel != LEVEL_STUDENT)
	{
		label = new QLabel(tr("Work phone"), contactFrame);
		label->setProperty("isFormLabel", true);
		contactBottomLayout->addWidget(label, 4, 0);
		workPhoneField = new QLineEdit(contactFrame);
		completer = new QCompleter(_userDataPlugin->listModel(), this);
		completer->setCompletionColumn(8);
		completer->setCaseSensitivity(Qt::CaseInsensitive);
		workPhoneField->setCompleter(completer);
		contactBottomLayout->addWidget(workPhoneField, 4, 1);
	}
	contactMainLayout->addLayout(contactBottomLayout);
	if (_user)
	{
		addressField->document()->setPlainText(_user->address());
		mailField->setText(_user->mail());
		homePhoneField->setText(_user->phone1());
		mobilePhoneField->setText(_user->phone3());
		if (_userLevel != LEVEL_STUDENT)
			workPhoneField->setText(_user->phone2());
	}
	return (contactFrame);
}

QWidget			*EditUser::getProfessionalFrame()
{
	QFrame		*professionalFrame;
	QGridLayout	*professionalBottomLayout;
	QBoxLayout	*professionalMainLayout;
	QLabel		*professionalTitle;
	QLabel		*label;
	QCompleter	*completer;

	professionalFrame = new QFrame();
	professionalFrame->setProperty("isFormFrame", true);
	professionalMainLayout = new QBoxLayout(QBoxLayout::TopToBottom, professionalFrame);
	professionalMainLayout->setSpacing(0);
	professionalMainLayout->setMargin(0);
	professionalTitle = new QLabel(tr("Professional informations"), professionalFrame);
	professionalTitle->setProperty("isFormTitle", true);
	professionalMainLayout->addWidget(professionalTitle);
	professionalBottomLayout = new QGridLayout();
	professionalBottomLayout->setSpacing(4);
	professionalBottomLayout->setMargin(8);
	professionalBottomLayout->setColumnMinimumWidth(0, 150);
	label = new QLabel(tr("Social insurance number"), professionalFrame);
	label->setProperty("isFormLabel", true);
	professionalBottomLayout->addWidget(label, 0, 0);
	socialInsuranceNbrField = new QLineEdit(professionalFrame);
	completer = new QCompleter(_userDataPlugin->listModel(), this);
	completer->setCompletionColumn(9);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	socialInsuranceNbrField->setCompleter(completer);
	professionalBottomLayout->addWidget(socialInsuranceNbrField, 0, 1);
	label = new QLabel(tr("Diplomes"), professionalFrame);
	label->setProperty("isFormLabel", true);
	professionalBottomLayout->addWidget(label, 1, 0);
	diplomaField = new QTextEdit(professionalFrame);
	professionalBottomLayout->addWidget(diplomaField, 1, 1);
	label = new QLabel(tr("Contract"), professionalFrame);
	label->setProperty("isFormLabel", true);
	professionalBottomLayout->addWidget(label, 2, 0);
	contractField = new QTextEdit(professionalFrame);
	professionalBottomLayout->addWidget(contractField, 2, 1);
	professionalMainLayout->addLayout(professionalBottomLayout);
	if (_user)
	{
		socialInsuranceNbrField->setText(_user->socialInsuranceNbr());
		diplomaField->document()->setPlainText(_user->diploma());
		contractField->document()->setPlainText(_user->contract());
	}
	return (professionalFrame);
}

QWidget			*EditUser::getStudiesFrame()
{
	QFrame		*studiesFrame;
	QGridLayout	*studiesBottomLayout;
	QBoxLayout	*studiesMainLayout;
	QLabel		*studiesTitle;
	QLabel		*label;

	studiesFrame = new QFrame();
	studiesFrame->setProperty("isFormFrame", true);
	studiesMainLayout = new QBoxLayout(QBoxLayout::TopToBottom, studiesFrame);
	studiesMainLayout->setSpacing(0);
	studiesMainLayout->setMargin(0);
	studiesTitle = new QLabel(tr("Schoolar informations"), studiesFrame);
	studiesTitle->setProperty("isFormTitle", true);
	studiesMainLayout->addWidget(studiesTitle);
	studiesBottomLayout = new QGridLayout();
	studiesBottomLayout->setSpacing(4);
	studiesBottomLayout->setMargin(8);
	studiesBottomLayout->setColumnMinimumWidth(0, 150);
	label = new QLabel(tr("Referent"), studiesFrame);
	label->setProperty("isFormLabel", true);
	studiesBottomLayout->addWidget(label, 0, 0);
	referentField = new QLineEdit(studiesFrame);
	studiesBottomLayout->addWidget(referentField, 0, 1, 1, 3);
	label = new QLabel(tr("Motive"), studiesFrame);
	label->setProperty("isFormLabel", true);
	studiesBottomLayout->addWidget(label, 1, 0);
	motiveField = new QTextEdit(studiesFrame);
	studiesBottomLayout->addWidget(motiveField, 1, 1, 1, 3);
	label = new QLabel(tr("Financial helps"), studiesFrame);
	label->setProperty("isFormLabel", true);
	studiesBottomLayout->addWidget(label, 2, 0);
	financialHelpsField = new QLineEdit(studiesFrame);
        studiesBottomLayout->addWidget(financialHelpsField, 2, 1, 1, 3);
	label = new QLabel(tr("Start year"), studiesFrame);
	label->setProperty("isFormLabel", true);
	studiesBottomLayout->addWidget(label, 3, 0);
	startYearField = new QSpinBox(studiesFrame);
	startYearField->setMinimum(1980);
	startYearField->setMaximum(2080);
	startYearField->setValue(QDate::currentDate().year());
	studiesBottomLayout->addWidget(startYearField, 3, 1);
	label = new QLabel(tr("Leave year"), studiesFrame);
	label->setProperty("isFormLabel", true);
	studiesBottomLayout->addWidget(label, 3, 2);
	leaveYearField = new QSpinBox(studiesFrame);
	leaveYearField->setMinimum(1980);
	leaveYearField->setMaximum(2080);
	leaveYearField->setValue(QDate::currentDate().year() + 1);
	studiesBottomLayout->addWidget(leaveYearField, 3, 3);
	label = new QLabel(tr("Repeated years"), studiesFrame);
	label->setProperty("isFormLabel", true);
	studiesBottomLayout->addWidget(label, 4, 0);
	repeatedYearsField = new QSpinBox(studiesFrame);
	repeatedYearsField->setMinimum(0);
	repeatedYearsField->setMaximum(10);
	studiesBottomLayout->addWidget(repeatedYearsField, 4, 1);
	label = new QLabel(tr("Skipped years"), studiesFrame);
	label->setProperty("isFormLabel", true);
	studiesBottomLayout->addWidget(label, 4, 2);
	skippedYearsField = new QSpinBox(studiesFrame);
	skippedYearsField->setMinimum(0);
	skippedYearsField->setMaximum(10);
	studiesBottomLayout->addWidget(skippedYearsField, 4, 3);
	label = new QLabel(tr("Post school follow up"), studiesFrame);
	label->setProperty("isFormLabel", true);
	studiesBottomLayout->addWidget(label, 5, 0);
	followUpField = new QTextEdit(studiesFrame);
	studiesBottomLayout->addWidget(followUpField, 5, 1, 1, 3);
	studiesMainLayout->addLayout(studiesBottomLayout);
	if (_user)
	{
		QStringList tmp = _user->comment().split("|:/:|:/|");

		if (tmp.count() >= 1)
			referentField->setText(tmp.at(0));
		motiveField->document()->setPlainText(_user->subscriptionReason());
		if (tmp.count() >= 2)
			financialHelpsField->setText(tmp.at(1));
		startYearField->setValue(_user->startYear());
		leaveYearField->setValue(_user->leaveYear());
		repeatedYearsField->setValue(_user->repeatedYears());
		if (tmp.count() >= 3)
			skippedYearsField->setValue(tmp.at(2).toInt());
		followUpField->document()->setPlainText(_user->followUp());
	}
	return (studiesFrame);
}

QWidget			*EditUser::getParentFrame()
{
	QFrame		*parentFrame;
	QGridLayout	*parentBottomLayout;
	QBoxLayout	*parentMainLayout;
	QLabel		*parentTitle;
	QLabel		*label;
	QCompleter	*completer;

	parentFrame = new QFrame(this);
	parentFrame->setProperty("isFormFrame", true);
	parentMainLayout = new QBoxLayout(QBoxLayout::TopToBottom, parentFrame);
	parentMainLayout->setSpacing(0);
	parentMainLayout->setMargin(0);
	parentTitle = new QLabel(tr("Parents informations"), parentFrame);
	parentTitle->setProperty("isFormTitle", true);
	parentMainLayout->addWidget(parentTitle);
	parentBottomLayout = new QGridLayout();
	parentBottomLayout->setSpacing(4);
	parentBottomLayout->setMargin(8);
	parentBottomLayout->setColumnMinimumWidth(0, 150);
	label = new QLabel(tr("Father last name"), parentFrame);
	label->setProperty("isFormLabel", true);
	parentBottomLayout->addWidget(label, 0, 0);
	fatherLastNameField = new QLineEdit(parentFrame);
	completer = new QCompleter(_userDataPlugin->listModel(), this);
	completer->setCompletionColumn(2);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	fatherLastNameField->setCompleter(completer);
	parentBottomLayout->addWidget(fatherLastNameField, 0, 1);
	label = new QLabel(tr("Mother last name"), parentFrame);
	label->setProperty("isFormLabel", true);
	parentBottomLayout->addWidget(label, 0, 2);
	motherLastNameField = new QLineEdit(parentFrame);
	completer = new QCompleter(_userDataPlugin->listModel(), this);
	completer->setCompletionColumn(2);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	motherLastNameField->setCompleter(completer);
	parentBottomLayout->addWidget(motherLastNameField, 0, 3);
	label = new QLabel(tr("Father first name"), parentFrame);
	label->setProperty("isFormLabel", true);
	parentBottomLayout->addWidget(label, 1, 0);
	fatherFirstNameField = new QLineEdit(parentFrame);
	completer = new QCompleter(_userDataPlugin->listModel(), this);
	completer->setCompletionColumn(3);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	fatherFirstNameField->setCompleter(completer);
	parentBottomLayout->addWidget(fatherFirstNameField, 1, 1);
	label = new QLabel(tr("Mother first name"), parentFrame);
	label->setProperty("isFormLabel", true);
	parentBottomLayout->addWidget(label, 1, 2);
	motherFirstNameField = new QLineEdit(parentFrame);
	completer = new QCompleter(_userDataPlugin->listModel(), this);
	completer->setCompletionColumn(3);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	motherFirstNameField->setCompleter(completer);
	parentBottomLayout->addWidget(motherFirstNameField, 1, 3);
	label = new QLabel(tr("Father occupation"), parentFrame);
	label->setProperty("isFormLabel", true);
	parentBottomLayout->addWidget(label, 2, 0);
	fatherOccupationField = new QLineEdit(parentFrame);
	completer = new QCompleter(_userDataPlugin->listModel(), this);
	completer->setCompletionColumn(10);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	fatherOccupationField->setCompleter(completer);
	parentBottomLayout->addWidget(fatherOccupationField, 2, 1);
	label = new QLabel(tr("Mother occupation"), parentFrame);
	label->setProperty("isFormLabel", true);
	parentBottomLayout->addWidget(label, 2, 2);
	motherOccupationField = new QLineEdit(parentFrame);
	completer = new QCompleter(_userDataPlugin->listModel(), this);
	completer->setCompletionColumn(10);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	motherOccupationField->setCompleter(completer);
	parentBottomLayout->addWidget(motherOccupationField, 2, 3);
	parentMainLayout->addLayout(parentBottomLayout);
	label = new QLabel(tr("Relationship"), parentFrame);
	label->setProperty("isFormLabel", true);
	parentBottomLayout->addWidget(label, 3, 0);
	relationshipField = new QComboBox(parentFrame);
	relationshipField->addItem(tr("Married"), "Married");
	relationshipField->addItem(tr("Divorced"), "Divorced");
	relationshipField->addItem(tr("Separated"), "Separated");
	relationshipField->addItem(tr("Deceaded"), "Deceaded");
	relationshipField->addItem(tr("Single"), "Single");
	relationshipField->addItem(tr("Other"), "Other");
	parentBottomLayout->addWidget(relationshipField, 3, 1, 1, 3);
	if (_user)
	{
		QList<UserData*>	parents;
		
		parents = _userDataPlugin->parentsOfStudent(_user);
		if (parents.size() >= 1)
		{
			if (parents[0]->gender() == GENDER_MALE)
				father = parents[0];
			else
				mother = parents[0];
			if (parents.size() > 1)
			{
				if (parents[1]->gender() == GENDER_MALE)
					father = parents[1];
				else
					mother = parents[1];
			}
		}
		if (father)
		{
			fatherLastNameField->setText(father->name());
			fatherFirstNameField->setText(father->surname());
			fatherOccupationField->setText(father->occupation());
		}
		if (mother)
		{
			motherLastNameField->setText(mother->name());
			motherFirstNameField->setText(mother->surname());
			motherOccupationField->setText(mother->occupation());
		}
		relationshipField->setCurrentIndex(relationshipField->findData(_user->relationship()));
	}
	connect(relationshipField, SIGNAL(currentIndexChanged(int)), this, SLOT(relationChanged(int)));
	return (parentFrame);
}

QWidget			*EditUser::getParentContactFrame()
{
	QFrame		*parentContactFrame;
	QGridLayout	*parentContactBottomLayout;
	QBoxLayout	*parentContactMainLayout;
	QLabel		*parentContactTitle;
	QLabel		*label;
	QCompleter	*completer;

	parentContactFrame = new QFrame(this);
	parentContactFrame->setProperty("isFormFrame", true);
	parentContactMainLayout = new QBoxLayout(QBoxLayout::TopToBottom, parentContactFrame);
	parentContactMainLayout->setSpacing(0);
	parentContactMainLayout->setMargin(0);
	parentContactTitle = new QLabel(tr("Parent contact informations"), parentContactFrame);
	parentContactTitle->setProperty("isFormTitle", true);
	parentContactMainLayout->addWidget(parentContactTitle);
	parentContactBottomLayout = new QGridLayout();
	parentContactBottomLayout->setSpacing(4);
	parentContactBottomLayout->setMargin(8);
	parentContactBottomLayout->setColumnMinimumWidth(0, 150);
	label = new QLabel(tr("Father address"), parentContactFrame);
	label->setProperty("isFormLabel", true);
	fatherLabels.append(label);
	parentContactBottomLayout->addWidget(label, 0, 0);
	fatherAddressField = new QTextEdit(parentContactFrame);
	parentContactBottomLayout->addWidget(fatherAddressField, 0, 1);
	label = new QLabel(tr("Mother address"), parentContactFrame);
	label->setProperty("isFormLabel", true);
	motherLabels.append(label);
	parentContactBottomLayout->addWidget(label, 0, 2);
	motherAddressField = new QTextEdit(parentContactFrame);
	parentContactBottomLayout->addWidget(motherAddressField, 0, 3);
	label = new QLabel(tr("Father email"), parentContactFrame);
	label->setProperty("isFormLabel", true);
	fatherLabels.append(label);
	parentContactBottomLayout->addWidget(label, 1, 0);
	fatherEmailField = new QLineEdit(parentContactFrame);
	completer = new QCompleter(_userDataPlugin->listModel(), this);
	completer->setCompletionColumn(5);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	fatherEmailField->setCompleter(completer);
	parentContactBottomLayout->addWidget(fatherEmailField, 1, 1);
	label = new QLabel(tr("Mother email"), parentContactFrame);
	label->setProperty("isFormLabel", true);
	motherLabels.append(label);
	parentContactBottomLayout->addWidget(label, 1, 2);
	motherEmailField = new QLineEdit(parentContactFrame);
	completer = new QCompleter(_userDataPlugin->listModel(), this);
	completer->setCompletionColumn(5);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	motherEmailField->setCompleter(completer);
	parentContactBottomLayout->addWidget(motherEmailField, 1, 3);
	label = new QLabel(tr("Father home phone"), parentContactFrame);
	label->setProperty("isFormLabel", true);
	fatherLabels.append(label);
	parentContactBottomLayout->addWidget(label, 2, 0);
	fatherHomePhoneField = new QLineEdit(parentContactFrame);
	completer = new QCompleter(_userDataPlugin->listModel(), this);
	completer->setCompletionColumn(6);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	fatherHomePhoneField->setCompleter(completer);
	parentContactBottomLayout->addWidget(fatherHomePhoneField, 2, 1);
	label = new QLabel(tr("Mother home phone"), parentContactFrame);
	label->setProperty("isFormLabel", true);
	motherLabels.append(label);
	parentContactBottomLayout->addWidget(label, 2, 2);
	motherHomePhoneField = new QLineEdit(parentContactFrame);
	completer = new QCompleter(_userDataPlugin->listModel(), this);
	completer->setCompletionColumn(6);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	motherHomePhoneField->setCompleter(completer);
	parentContactBottomLayout->addWidget(motherHomePhoneField, 2, 3);
	label = new QLabel(tr("Father mobile phone"), parentContactFrame);
	label->setProperty("isFormLabel", true);
	fatherLabels.append(label);
	parentContactBottomLayout->addWidget(label, 3, 0);
	fatherMobilePhoneField = new QLineEdit(parentContactFrame);
	completer = new QCompleter(_userDataPlugin->listModel(), this);
	completer->setCompletionColumn(7);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	fatherMobilePhoneField->setCompleter(completer);
	parentContactBottomLayout->addWidget(fatherMobilePhoneField, 3, 1);
	label = new QLabel(tr("Mother mobile phone"), parentContactFrame);
	label->setProperty("isFormLabel", true);
	motherLabels.append(label);
	parentContactBottomLayout->addWidget(label, 3, 2);
	motherMobilePhoneField = new QLineEdit(parentContactFrame);
	completer = new QCompleter(_userDataPlugin->listModel(), this);
	completer->setCompletionColumn(7);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	motherMobilePhoneField->setCompleter(completer);
	parentContactBottomLayout->addWidget(motherMobilePhoneField, 3, 3);
	label = new QLabel(tr("Father work phone"), parentContactFrame);
	label->setProperty("isFormLabel", true);
	fatherLabels.append(label);
	parentContactBottomLayout->addWidget(label, 4, 0);
	fatherWorkPhoneField = new QLineEdit(parentContactFrame);
	completer = new QCompleter(_userDataPlugin->listModel(), this);
	completer->setCompletionColumn(8);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	fatherWorkPhoneField->setCompleter(completer);
	parentContactBottomLayout->addWidget(fatherWorkPhoneField, 4, 1);
	label = new QLabel(tr("Mother work phone"), parentContactFrame);
	label->setProperty("isFormLabel", true);
	motherLabels.append(label);
	parentContactBottomLayout->addWidget(label, 4, 2);
	motherWorkPhoneField = new QLineEdit(parentContactFrame);
	completer = new QCompleter(_userDataPlugin->listModel(), this);
	completer->setCompletionColumn(8);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	motherWorkPhoneField->setCompleter(completer);
	parentContactBottomLayout->addWidget(motherWorkPhoneField, 4, 3);
	parentContactMainLayout->addLayout(parentContactBottomLayout);
	if (!_user || _user->relationship() == "Married" || _user->relationship() == "Deceaded")
	{
		fatherLabels.at(0)->setText(tr("Parents address"));
		fatherLabels.at(1)->setText(tr("Parents email"));
		fatherLabels.at(2)->setText(tr("Parents home phone"));
		fatherLabels.at(3)->setText(tr("Parents mobile phone"));
		fatherLabels.at(4)->setText(tr("Parents work phone"));
		foreach (QWidget *widget, motherLabels)
			widget->hide();
		motherAddressField->hide();
		motherEmailField->hide();
		motherHomePhoneField->hide();
		motherMobilePhoneField->hide();
		motherWorkPhoneField->hide();
	}
	if (father)
	{
		fatherAddressField->document()->setPlainText(father->address());
		fatherEmailField->setText(father->mail());
		fatherHomePhoneField->setText(father->phone1());
		fatherMobilePhoneField->setText(father->phone3());
		fatherWorkPhoneField->setText(father->phone2());
	}
	if (mother)
	{
		motherAddressField->document()->setPlainText(mother->address());
		motherEmailField->setText(mother->mail());
		motherHomePhoneField->setText(mother->phone1());
		motherMobilePhoneField->setText(mother->phone3());
		motherWorkPhoneField->setText(mother->phone2());
	}
	return (parentContactFrame);
}

void			EditUser::saved()
{
	error = false;
	applied();
	if ( ! error)
		exited();
}

void			EditUser::applied()
{
	bool		editing;

	editing = false;
	if (_user)
		editing = true;
	else
	{
		_user = _userDataPlugin->createUser(firstNameField->text() + lastNameField->text()); // TODO find unused login
		_user->setPassword(_user->login());
		if (_userLevel == LEVEL_STUDENT)
		{
			father = _userDataPlugin->createUser(fatherFirstNameField->text() + fatherLastNameField->text()); // TODO find unused login
			father->setPassword(father->login());
			father->setStudent(_user);
			father->setGender(GENDER_MALE);
			father->setLevel(LEVEL_FAMILY);
			mother = _userDataPlugin->createUser(motherFirstNameField->text() + motherLastNameField->text()); // TODO find unused login
			mother->setPassword(mother->login());
			mother->setStudent(_user);
			mother->setGender(GENDER_FEMALE);
			mother->setLevel(LEVEL_FAMILY);
		}
	}
	_user->setEnable(true);
	_user->setName(lastNameField->text());
	_user->setSurname(firstNameField->text());
	if (_user->name().isEmpty() || _user->surname().isEmpty())
		error = true;

	_user->setGender(static_cast<UserGender>(genderField->itemData(genderField->currentIndex()).toInt()));
	_user->setBirthDate(birthDateField->date());
	_user->setBornPlace(birthPlaceField->text());
	_user->setAddress(addressField->document()->toPlainText());
	_user->setMail(mailField->text());
	_user->setPhone1(homePhoneField->text());
	_user->setPhone3(mobilePhoneField->text());
	_user->setLevel(_userLevel);
	if (_userLevel != LEVEL_STUDENT)
	{
		_user->setPhone2(workPhoneField->text());
		_user->setSocialInsuranceNbr(socialInsuranceNbrField->text());
		_user->setDiploma(diplomaField->document()->toPlainText());
		_user->setContract(contractField->document()->toPlainText());
	}
	else
	{
		if (_node)
			_user->setStudentClass(_node);
		_user->setNbrBrothers(siblingsField->value());
		_user->setComment(referentField->text() + "|:/:|:/|" + financialHelpsField->text() + "|:/:|:/|" + QString::number(skippedYearsField->value()) + "|:/:|:/|");
		_user->setSubscriptionReason(motiveField->document()->toPlainText());
		_user->setStartYear(startYearField->value());
		_user->setLeaveYear(leaveYearField->value());
		_user->setRepeatedYears(repeatedYearsField->value());
		_user->setFollowUp(followUpField->document()->toPlainText());
		_user->setRelationship(relationshipField->itemData(relationshipField->currentIndex()).toString());
		if (father)
		{
			father->setName(fatherLastNameField->text());
			father->setSurname(fatherFirstNameField->text());
			father->setOccupation(fatherOccupationField->text());
			father->setAddress(fatherAddressField->document()->toPlainText());
			father->setMail(fatherEmailField->text());
			father->setPhone1(fatherHomePhoneField->text());
			father->setPhone3(fatherMobilePhoneField->text());
			father->setPhone2(fatherWorkPhoneField->text());
		}
		if (mother)
		{
			mother->setName(motherLastNameField->text());
			mother->setSurname(motherFirstNameField->text());
			mother->setOccupation(motherOccupationField->text());
			mother->setAddress(motherAddressField->document()->toPlainText());
			mother->setMail(motherEmailField->text());
			mother->setPhone1(motherHomePhoneField->text());
			mother->setPhone3(motherMobilePhoneField->text());
			mother->setPhone2(motherWorkPhoneField->text());
		}
	}

	if (error)
		return;

	if (editing)
		_user->save();
	else
		_user->create();
	if (_userLevel == LEVEL_STUDENT)
	{
		if (editing)
		{
			if (father)
				father->save();
			if (mother)
				mother->save();
		}
		else
		{
			if (father)
				father->create();
			if (mother)
				mother->create();
		}
	}
}

void			EditUser::exited()
{
	emit exit();
}

void			EditUser::reseted()
{
	firstNameField->clear();
	lastNameField->clear();
	genderField->setCurrentIndex(0);
	birthDateField->setDate(QDate::currentDate());
	birthPlaceField->clear();
	addressField->clear();
	mailField->clear();
	homePhoneField->clear();
	mobilePhoneField->clear();
	if (_userLevel != LEVEL_STUDENT)
	{
		workPhoneField->clear();
		socialInsuranceNbrField->clear();
		diplomaField->clear();
		contractField->clear();
	}
	else
	{
		siblingsField->clear();
		referentField->clear();
		motiveField->clear();
		financialHelpsField->clear();
		startYearField->clear();
		leaveYearField->clear();
		repeatedYearsField->clear();
		skippedYearsField->clear();
		followUpField->clear();
		fatherLastNameField->clear();
		motherLastNameField->clear();
		fatherFirstNameField->clear();
		motherFirstNameField->clear();
		fatherOccupationField->clear();
		motherOccupationField->clear();
		relationshipField->setCurrentIndex(0);
		fatherAddressField->clear();
		motherAddressField->clear();
		fatherEmailField->clear();
		motherEmailField->clear();
		fatherHomePhoneField->clear();
		motherHomePhoneField->clear();
		fatherMobilePhoneField->clear();
		motherMobilePhoneField->clear();
		fatherWorkPhoneField->clear();
		motherWorkPhoneField->clear();
	}
}

void			EditUser::relationChanged(int index)
{
	if (relationshipField->itemData(index) == "Married" || relationshipField->itemData(index) == "Deceaded")
	{
		fatherLabels.at(0)->setText(tr("Parents address"));
		fatherLabels.at(1)->setText(tr("Parents email"));
		fatherLabels.at(2)->setText(tr("Parents home phone"));
		fatherLabels.at(3)->setText(tr("Parents mobile phone"));
		fatherLabels.at(4)->setText(tr("Parents work phone"));
		foreach (QWidget *widget, motherLabels)
			widget->hide();
		motherAddressField->hide();
		motherEmailField->hide();
		motherHomePhoneField->hide();
		motherMobilePhoneField->hide();
		motherWorkPhoneField->hide();
	}
	else
	{
		fatherLabels.at(0)->setText(tr("Father address"));
		fatherLabels.at(1)->setText(tr("Father email"));
		fatherLabels.at(2)->setText(tr("Father home phone"));
		fatherLabels.at(3)->setText(tr("Father mobile phone"));
		fatherLabels.at(4)->setText(tr("Father work phone"));
		foreach (QWidget *widget, motherLabels)
			widget->show();
		motherAddressField->show();
		motherEmailField->show();
		motherHomePhoneField->show();
		motherMobilePhoneField->show();
		motherWorkPhoneField->show();
	}
}
