#include		"EditParent.h"

#include		<QGridLayout>
#include		<QBoxLayout>
#include		<QFrame>
#include		<QLabel>
#include		<QPushButton>

//EditParent::EditParent(QWidget *parent, PluginManager *pluginManager, UserData *user) : QWidget(parent), _pluginManager(pluginManager), _user(user)
EditParent::EditParent(UserData *father, UserData *mother)
{
	setupUi();
	//rightLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	//rightLayout->setMargin(0);
	//rightLayout->setSpacing(2);
	//informationsFrame = new QFrame(this);
	//informationsLayout = new QBoxLayout(QBoxLayout::TopToBottom, informationsFrame);
	//informationsLayout->setSpacing(0);
	//informationsLayout->setMargin(0);
	//informationsFrame->setMinimumWidth(200);
	//informationsTitle = new QLabel(tr("Informations:"), informationsFrame);
	//informationsTitle->setProperty("isTitle", true);
	//informationsTitle->setProperty("isRound", true);
	//informationsLayout->addWidget(informationsTitle);
	//rightLayout->addWidget(informationsFrame);
	//actionsTitle = new QLabel(tr("Actions:"), this);
	//actionsTitle->setProperty("isTitle", true);
	//actionsTitle->setProperty("isRound", true);
	//rightLayout->addWidget(actionsTitle);
	//okButton = new QPushButton(QIcon(":/Icons/ok.png"), tr("OK"), this);
	//rightLayout->addWidget(okButton);
	//applyButton = new QPushButton(QIcon(":/Icons/save.png"), tr("Apply"), this);
	//rightLayout->addWidget(applyButton);
	//resetButton = new QPushButton(QIcon(":/Icons/reset.png"), tr("Reset"), this);
	//rightLayout->addWidget(resetButton);
	//cancelButton = new QPushButton(QIcon(":/Icons/back.png"), tr("Cancel"), this);
	//rightLayout->addWidget(cancelButton);
	//rightLayout->addWidget(new QWidget(this), 1);
	//mainLayout->addLayout(rightLayout);
	//connect(okButton, SIGNAL(clicked()), this, SLOT(saved()));
	//connect(okButton, SIGNAL(clicked()), this, SLOT(exited()));
	//connect(applyButton, SIGNAL(clicked()), this, SLOT(saved()));
	//connect(resetButton, SIGNAL(clicked()), this, SLOT(reseted()));
	//connect(cancelButton, SIGNAL(clicked()), this, SLOT(exited()));
	if (father && mother)
	{
		firstNameFatherField->setText(father->surname());
		firstNameMotherField->setText(mother->surname());
		lastNameFatherField->setText(father->name());
		lastNameMotherField->setText(mother->name());
		relationshipField->setCurrentIndex(relationshipField->findData(father->relationship()));
		addressField->document()->setPlainText(father->address());
		mailField->setText(father->mail());
		homePhoneField->setText(father->phone1());
		workPhoneField->setText(father->phone2());
		mobilePhoneField->setText(father->phone3());
		occupationalCategoryFatherField->setText(father->proCategory());
		occupationalCategoryMotherField->setText(mother->proCategory());
		occupationFatherField->setText(father->occupation());
		occupationMotherField->setText(mother->occupation());
	}
}

void        EditParent::setupUi()
{
	QBoxLayout	*mainLayout;
	QBoxLayout	*leftLayout;
	QBoxLayout	*rightLayout;
	QBoxLayout	*informationsLayout;
	QGridLayout	*personnalBottomLayout;
	QGridLayout	*contactBottomLayout;
	QGridLayout	*occupationBottomLayout;
	QBoxLayout	*personnalMainLayout;
	QBoxLayout	*contactMainLayout;
	QBoxLayout	*occupationMainLayout;
	QFrame		*personnalFrame;
	QFrame		*contactFrame;
	QFrame		*occupationFrame;
	QFrame		*informationsFrame;
	QLabel		*personnalTitle;
	QLabel		*contactTitle;
	QLabel		*occupationTitle;
	QLabel		*informationsTitle;
	QLabel		*actionsTitle;
	QLabel		*label;
	QPushButton	*applyButton;
	QPushButton	*okButton;
	QPushButton	*resetButton;
	QPushButton	*cancelButton;

	mainLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
	mainLayout->setSpacing(0);
	mainLayout->setMargin(0);
	leftLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	leftLayout->setSpacing(0);
	leftLayout->setMargin(0);
	personnalFrame = new QFrame(this);
	personnalFrame->setProperty("isFormFrame", true);
	personnalMainLayout = new QBoxLayout(QBoxLayout::TopToBottom, personnalFrame);
	personnalMainLayout->setSpacing(0);
	personnalMainLayout->setMargin(0);
	personnalTitle = new QLabel(tr("Parents informations"), personnalFrame);
	personnalTitle->setProperty("isFormTitle", true);
	personnalMainLayout->addWidget(personnalTitle);
	personnalBottomLayout = new QGridLayout();
	personnalBottomLayout->setSpacing(4);
	personnalBottomLayout->setMargin(8);
	personnalBottomLayout->setColumnMinimumWidth(0, 150);
	label = new QLabel(tr("Father last name"), personnalFrame);
	label->setProperty("isFormLabel", true);
	personnalBottomLayout->addWidget(label, 0, 0);
	lastNameFatherField = new QLineEdit(personnalFrame);
	personnalBottomLayout->addWidget(lastNameFatherField, 0, 1);
	label = new QLabel(tr("Mother last name"), personnalFrame);
	label->setProperty("isFormLabel", true);
	personnalBottomLayout->addWidget(label, 1, 0);
	lastNameMotherField = new QLineEdit(personnalFrame);
	personnalBottomLayout->addWidget(lastNameMotherField, 1, 1);
	label = new QLabel(tr("Father first name"), personnalFrame);
	label->setProperty("isFormLabel", true);
	personnalBottomLayout->addWidget(label, 2, 0);
	firstNameFatherField = new QLineEdit(personnalFrame);
	personnalBottomLayout->addWidget(firstNameFatherField, 2, 1);
	label = new QLabel(tr("Mother first name"), personnalFrame);
	label->setProperty("isFormLabel", true);
	personnalBottomLayout->addWidget(label, 3, 0);
	firstNameMotherField = new QLineEdit(personnalFrame);
	personnalBottomLayout->addWidget(firstNameMotherField, 3, 1);
	label = new QLabel(tr("Relationship"), personnalFrame);
	label->setProperty("isFormLabel", true);
	personnalBottomLayout->addWidget(label, 4, 0);
	relationshipField = new QComboBox(personnalFrame);
	relationshipField->addItem(tr("Parent"), "Parent");
	relationshipField->addItem(tr("Tutor"), "Tutor");
	relationshipField->addItem(tr("Unknow"), "Unknow");
	personnalBottomLayout->addWidget(relationshipField, 4, 1);
	personnalMainLayout->addLayout(personnalBottomLayout);
	leftLayout->addWidget(personnalFrame);
	contactFrame = new QFrame(this);
	contactFrame->setProperty("isFormFrame", true);
	contactMainLayout = new QBoxLayout(QBoxLayout::TopToBottom, contactFrame);
	contactMainLayout->setSpacing(0);
	contactMainLayout->setMargin(0);
	contactTitle = new QLabel(tr("Parent contact informations"), contactFrame);
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
	contactBottomLayout->addWidget(mailField, 1, 1);
	label = new QLabel(tr("Home phone"), contactFrame);
	label->setProperty("isFormLabel", true);
	contactBottomLayout->addWidget(label, 2, 0);
	homePhoneField = new QLineEdit(contactFrame);
	contactBottomLayout->addWidget(homePhoneField, 2, 1);
	label = new QLabel(tr("Work phone"), contactFrame);
	label->setProperty("isFormLabel", true);
	contactBottomLayout->addWidget(label, 3, 0);
	workPhoneField = new QLineEdit(contactFrame);
	contactBottomLayout->addWidget(workPhoneField, 3, 1);
	label = new QLabel(tr("Mobile phone"), contactFrame);
	label->setProperty("isFormLabel", true);
	contactBottomLayout->addWidget(label, 4, 0);
	mobilePhoneField = new QLineEdit(contactFrame);
	contactBottomLayout->addWidget(mobilePhoneField, 4, 1);
	contactMainLayout->addLayout(contactBottomLayout);
	leftLayout->addWidget(contactFrame);
	occupationFrame = new QFrame(this);
	occupationFrame->setProperty("isFormFrame", true);
	occupationMainLayout = new QBoxLayout(QBoxLayout::TopToBottom, occupationFrame);
	occupationMainLayout->setSpacing(0);
	occupationMainLayout->setMargin(0);
	occupationTitle = new QLabel(tr("Parent occupation informations"), occupationFrame);
	occupationTitle->setProperty("isFormTitle", true);
	occupationMainLayout->addWidget(occupationTitle);
	occupationBottomLayout = new QGridLayout();
	occupationBottomLayout->setSpacing(4);
	occupationBottomLayout->setMargin(8);
	occupationBottomLayout->setColumnMinimumWidth(0, 150);
	label = new QLabel(tr("Father occupational category"), occupationFrame);
	label->setProperty("isFormLabel", true);
	occupationBottomLayout->addWidget(label, 0, 0);
	occupationalCategoryFatherField = new QLineEdit(occupationFrame);
	occupationBottomLayout->addWidget(occupationalCategoryFatherField, 0, 1);
	label = new QLabel(tr("Mother occupational category"), occupationFrame);
	label->setProperty("isFormLabel", true);
	occupationBottomLayout->addWidget(label, 1, 0);
	occupationalCategoryMotherField = new QLineEdit(occupationFrame);
	occupationBottomLayout->addWidget(occupationalCategoryMotherField, 1, 1);
	label = new QLabel(tr("Father occupation"), occupationFrame);
	label->setProperty("isFormLabel", true);
	occupationBottomLayout->addWidget(label, 2, 0);
	occupationFatherField = new QLineEdit(occupationFrame);
	occupationBottomLayout->addWidget(occupationFatherField, 2, 1);
	label = new QLabel(tr("Mother occupation"), occupationFrame);
	label->setProperty("isFormLabel", true);
	occupationBottomLayout->addWidget(label, 3, 0);
	occupationMotherField = new QLineEdit(occupationFrame);
	occupationBottomLayout->addWidget(occupationMotherField, 3, 1);
	occupationMainLayout->addLayout(occupationBottomLayout);
	leftLayout->addWidget(occupationFrame);
	mainLayout->addLayout(leftLayout);
}

//void			EditParent::saved()
//{
//	bool		editing;
//
//	editing = false;
//	if (_user)
//		editing = true;
//	else
//	{
//		_user = _pluginManager->findPlugin<UserDataPlugin *>()->createUser(firstNameField->text() + lastNameField->text()); // TODO find unused login
//		_user->setPassword(_user->login());
//	}
//	_user->setEnable(true);
//	_user->setName(lastNameField->text());
//	_user->setSurname(firstNameField->text());
//	_user->setGender(static_cast<UserGender>(genderField->itemData(genderField->currentIndex()).toInt()));
//	_user->setBirthDate(birthDateField->date());
//	_user->setRelationship(relationshipField->itemData(relationshipField->currentIndex()).toString());
//	_user->setAddress(addressField->document()->toPlainText());
//	_user->setMail(mailField->text());
//	_user->setPhone1(homePhoneField->text());
//	_user->setPhone2(workPhoneField->text());
//	_user->setPhone3(mobilePhoneField->text());
//	_user->setOccupation(occupationField->text());
//	_user->setProCategory(occupationalCategoryField->text());
//	_user->setLevel(LEVEL_FAMILY);
//	if (editing)
//		_user->save();
//	else
//		_user->create();
//}

//void			EditParent::exited()
//{
//	emit exit();
//}

//void			EditParent::reseted()
//{
//	firstNameField->clear();
//	lastNameField->clear();
//	genderField->setCurrentIndex(0);
//	birthDateField->setDate(QDate::currentDate());
//	relationshipField->clear();
//	addressField->clear();
//	mailField->clear();
//	homePhoneField->clear();
//	workPhoneField->clear();
//	mobilePhoneField->clear();
//	occupationalCategoryField->clear();
//	occupationField->clear();
//}