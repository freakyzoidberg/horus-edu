#include "FormStudents.h"

#include	<QLabel>

FormStudents::FormStudents(QList<UserData*> list)
{
    QVBoxLayout *FormLayout = new QVBoxLayout(this);
	QLabel	*label;

    FormLayout->setSpacing(0);
    FormLayout->setMargin(0);

	label = new QLabel(tr("Basic informations"), this);
	label->setProperty("isFormTitle", true);
	FormLayout->addWidget(label);
    BaseInfos = new BasicInfos();
    FormLayout->addWidget(BaseInfos);

	//label = new QLabel(tr("Parent informations"), this);
	label->setProperty("isFormTitle", true);
	FormLayout->addWidget(label);
    ParInfos = new ParentInfos();
    ParInfos->getParent()->addItem(tr("none"), 0);
    foreach (UserData* mud, list)
    {
qDebug() << mud->login();
        ParInfos->getParent()->addItem(mud->surname()+" "+mud->name(), mud->id());
    }


    FormLayout->addWidget(ParInfos);

	label = new QLabel(tr("Social informations"), this);
	label->setProperty("isFormTitle", true);
	FormLayout->addWidget(label);
    SocInfos = new SocialInfos();
    FormLayout->addWidget(SocInfos);


	label = new QLabel(tr("Scholar informations"), this);
	label->setProperty("isFormTitle", true);
	FormLayout->addWidget(label);
    SchoInfos = new SchoolInfos();
    FormLayout->addWidget(SchoInfos);

	//label = new QLabel(tr("Follow up"), this);
	label->setProperty("isFormTitle", true);
	FormLayout->addWidget(label);
    SuiInfos = new SuiviInfos();
    FormLayout->addWidget(SuiInfos);
    id = 0;
    this->setLayout(FormLayout);
}

FormStudents::FormStudents(QList<UserData*> list, QList<UserData*> parentlist,UserData *d)
{
    QVBoxLayout *FormLayout = new QVBoxLayout(this);
    FormLayout->setSpacing(0);
    FormLayout->setMargin(0);
    id = d->id();


    qDebug() << d;
    BaseInfos = new BasicInfos(d);
    FormLayout->addWidget(BaseInfos);

    ParInfos = new ParentInfos(d);
    ParInfos->getParent()->addItem(tr("none"), 0);
    foreach (UserData* mud, list)
    {
        ParInfos->getParent()->addItem(mud->surname()+" "+mud->name(), mud->id());
    }


if (parentlist.count() > 0)
    ParInfos->getParent()->setCurrentIndex(ParInfos->getParent()->findData(parentlist.first()->id(), Qt::UserRole, Qt::MatchCaseSensitive));
    FormLayout->addWidget(ParInfos);

    SocInfos = new SocialInfos(d);
    FormLayout->addWidget(SocInfos);


    SchoInfos = new SchoolInfos(d);
    FormLayout->addWidget(SchoInfos);

    SuiInfos = new SuiviInfos(d);
    FormLayout->addWidget(SuiInfos);


    this->setLayout(FormLayout);
}
