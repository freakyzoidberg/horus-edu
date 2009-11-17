#include		"EditParent.h"

#include		<QGridLayout>
#include		<QBoxLayout>
#include		<QFrame>
#include		<QLabel>
#include		<QPushButton>

EditParent::EditParent(QWidget *parent, PluginManager *pluginManager, UserData *user) : QWidget(parent), _pluginManager(pluginManager), _user(user)
{
	QGridLayout	*mainLayout;
	QGridLayout	*personnalBottomLayout;
	QGridLayout	*contactBottomLayout;
	QGridLayout	*occupationBottomLayout;
	QGridLayout	*actionsBottomLayout;
	QBoxLayout	*personnalMainLayout;
	QBoxLayout	*contactMainLayout;
	QBoxLayout	*occupationMainLayout;
	QBoxLayout	*actionsMainLayout;
	QFrame		*personnalFrame;
	QFrame		*contactFrame;
	QFrame		*occupationFrame;
	QFrame		*actionsFrame;
	QLabel		*personnalTitle;
	QLabel		*contactTitle;
	QLabel		*occupationTitle;
	QLabel		*actionsTitle;
	QPushButton	*applyButton;
	QPushButton	*okButton;
	QPushButton	*resetButton;
	QPushButton	*cancelButton;

	mainLayout = new QGridLayout(this);
	personnalFrame = new QFrame(this);
	personnalMainLayout = new QBoxLayout(QBoxLayout::TopToBottom, personnalFrame);
	personnalTitle = new QLabel(tr("Personnal informations"), personnalFrame);
	personnalMainLayout->addWidget(personnalTitle, 0, Qt::AlignTop);
	personnalBottomLayout = new QGridLayout();
	personnalBottomLayout->addWidget(new QLabel(tr("Last name"), personnalFrame), 0, 0);
	lastNameField = new QLineEdit(personnalFrame);
	personnalBottomLayout->addWidget(lastNameField, 0, 1);
	personnalBottomLayout->addWidget(new QLabel(tr("First name"), personnalFrame), 1, 0);
	firstNameField = new QLineEdit(personnalFrame);
	personnalBottomLayout->addWidget(firstNameField, 1, 1);
	personnalBottomLayout->addWidget(new QLabel(tr("Gender"), personnalFrame), 2, 0);
	genderField = new QComboBox(personnalFrame);
	genderField->addItem(tr("Unknow"), GENDER_UNKNOW);
	genderField->addItem(tr("Female"), GENDER_FEMALE);
	genderField->addItem(tr("Male"), GENDER_MALE);
	personnalBottomLayout->addWidget(genderField, 2, 1);
	personnalBottomLayout->addWidget(new QLabel(tr("Birth date"), personnalFrame), 3, 0);
	birthDateField = new QDateEdit(personnalFrame);
	personnalBottomLayout->addWidget(birthDateField, 3, 1);
	personnalBottomLayout->addWidget(new QLabel(tr("Relationship"), personnalFrame), 4, 0);
	relationshipField = new QComboBox(personnalFrame);
	relationshipField->addItem(tr("Parent"), "Parent");
	relationshipField->addItem(tr("Tutor"), "Tutor");
	relationshipField->addItem(tr("Unknow"), "Unknow");
	personnalBottomLayout->addWidget(relationshipField, 4, 1);
	personnalMainLayout->addLayout(personnalBottomLayout);
	mainLayout->addWidget(personnalFrame, 0, 0);
	contactFrame = new QFrame(this);
	contactMainLayout = new QBoxLayout(QBoxLayout::TopToBottom, contactFrame);
	contactTitle = new QLabel(tr("Contact informations"), contactFrame);
	contactMainLayout->addWidget(contactTitle, 0, Qt::AlignTop);
	contactBottomLayout = new QGridLayout();
	contactBottomLayout->addWidget(new QLabel(tr("Address"), contactFrame), 0, 0);
	addressField = new QTextEdit(contactFrame);
	contactBottomLayout->addWidget(addressField, 0, 1);
	contactBottomLayout->addWidget(new QLabel(tr("Email"), contactFrame), 1, 0);
	mailField = new QLineEdit(contactFrame);
	contactBottomLayout->addWidget(mailField, 1, 1);
	contactBottomLayout->addWidget(new QLabel(tr("Home phone"), contactFrame), 2, 0);
	homePhoneField = new QLineEdit(contactFrame);
	contactBottomLayout->addWidget(homePhoneField, 2, 1);
	contactBottomLayout->addWidget(new QLabel(tr("Work phone"), contactFrame), 3, 0);
	workPhoneField = new QLineEdit(contactFrame);
	contactBottomLayout->addWidget(workPhoneField, 3, 1);
	contactBottomLayout->addWidget(new QLabel(tr("Mobile phone"), contactFrame), 4, 0);
	mobilePhoneField = new QLineEdit(contactFrame);
	contactBottomLayout->addWidget(mobilePhoneField, 4, 1);
	contactMainLayout->addLayout(contactBottomLayout);
	mainLayout->addWidget(contactFrame, 0, 1);
	occupationFrame = new QFrame(this);
	occupationMainLayout = new QBoxLayout(QBoxLayout::TopToBottom, occupationFrame);
	occupationTitle = new QLabel(tr("Occupation informations"), occupationFrame);
	occupationMainLayout->addWidget(occupationTitle, 0, Qt::AlignTop);
	occupationBottomLayout = new QGridLayout();
	occupationBottomLayout->addWidget(new QLabel(tr("Occupational category"), occupationFrame), 0, 0);
	occupationalCategoryField = new QLineEdit(occupationFrame);
	occupationBottomLayout->addWidget(occupationalCategoryField, 0, 1);
	occupationBottomLayout->addWidget(new QLabel(tr("Occupation"), occupationFrame), 1, 0);
	occupationField = new QLineEdit(occupationFrame);
	occupationBottomLayout->addWidget(occupationField, 1, 1);
	occupationMainLayout->addLayout(occupationBottomLayout);
	mainLayout->addWidget(occupationFrame, 1, 0);
	actionsFrame = new QFrame(this);
	actionsMainLayout = new QBoxLayout(QBoxLayout::TopToBottom, actionsFrame);
	actionsTitle = new QLabel(tr("Actions"), actionsFrame);
	actionsMainLayout->addWidget(actionsTitle, 0, Qt::AlignTop);
	actionsBottomLayout = new QGridLayout();
	okButton = new QPushButton(tr("OK"), actionsFrame);
	actionsBottomLayout->addWidget(okButton, 0, 0);
	applyButton = new QPushButton(tr("Apply"), actionsFrame);
	actionsBottomLayout->addWidget(applyButton, 0, 1);
	resetButton = new QPushButton(tr("Reset"), actionsFrame);
	actionsBottomLayout->addWidget(resetButton, 1, 0);
	cancelButton = new QPushButton(tr("Cancel"), actionsFrame);
	actionsBottomLayout->addWidget(cancelButton, 1, 1);
	actionsMainLayout->addLayout(actionsBottomLayout);
	mainLayout->addWidget(actionsFrame, 1, 1);
	connect(okButton, SIGNAL(clicked()), this, SLOT(saved()));
	connect(okButton, SIGNAL(clicked()), this, SLOT(exited()));
	connect(applyButton, SIGNAL(clicked()), this, SLOT(saved()));
	connect(resetButton, SIGNAL(clicked()), this, SLOT(reseted()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(exited()));
	if (user)
	{
		firstNameField->setText(user->surname());
		lastNameField->setText(user->name());
		genderField->setCurrentIndex(genderField->findData(user->gender()));
		birthDateField->setDate(user->birthDate());
		relationshipField->setCurrentIndex(relationshipField->findData(user->relationship()));
		addressField->document()->setPlainText(user->address());
		mailField->setText(user->mail());
		homePhoneField->setText(user->phone1());
		workPhoneField->setText(user->phone2());
		mobilePhoneField->setText(user->phone3());
		occupationalCategoryField->setText(user->proCategory());
		occupationField->setText(user->occupation());
	}
}

void			EditParent::saved()
{
	bool		editing;

	editing = false;
	if (_user)
		editing = true;
	else
	{
		_user = _pluginManager->findPlugin<UserDataPlugin *>()->createUser(firstNameField->text() + lastNameField->text()); // TODO find unused login
		_user->setPassword(_user->login());
	}
	_user->setName(lastNameField->text());
	_user->setSurname(firstNameField->text());
	_user->setGender(static_cast<UserGender>(genderField->itemData(genderField->currentIndex()).toInt()));
	_user->setBirthDate(birthDateField->date());
	_user->setRelationship(relationshipField->itemData(relationshipField->currentIndex()).toString());
	_user->setAddress(addressField->document()->toPlainText());
	_user->setMail(mailField->text());
	_user->setPhone1(homePhoneField->text());
	_user->setPhone2(workPhoneField->text());
	_user->setPhone3(mobilePhoneField->text());
	_user->setOccupation(occupationField->text());
	_user->setProCategory(occupationalCategoryField->text());
	_user->setLevel(LEVEL_FAMILY);
	if (editing)
		_user->save();
	else
		_user->create();
}

void			EditParent::exited()
{
	emit exit();
}

void			EditParent::reseted()
{
	firstNameField->clear();
	lastNameField->clear();
	genderField->setCurrentIndex(0);
	birthDateField->setDate(QDate::currentDate());
	relationshipField->clear();
	addressField->clear();
	mailField->clear();
	homePhoneField->clear();
	workPhoneField->clear();
	mobilePhoneField->clear();
	occupationalCategoryField->clear();
	occupationField->clear();
}
