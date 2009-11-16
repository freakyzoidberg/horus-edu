#include "FormStudents.h"

FormStudents::FormStudents(QList<UserData*> list)
{
    QVBoxLayout *FormLayout = new QVBoxLayout(this);

    BaseInfos = new BasicInfos();
    FormLayout->addWidget(BaseInfos);

    ParInfos = new ParentInfos();
    ParInfos->getParent()->addItem(tr("none"), 0);
    foreach (UserData* mud, list)
    ParInfos->getParent()->addItem(mud->surname()+" "+mud->name(), mud->id());
    FormLayout->addWidget(ParInfos);

    SocInfos = new SocialInfos();
    FormLayout->addWidget(SocInfos);


    SchoInfos = new SchoolInfos();
    FormLayout->addWidget(SchoInfos);

    SuiInfos = new SuiviInfos();
    FormLayout->addWidget(SuiInfos);
    id = 0;
    this->setLayout(FormLayout);
}

FormStudents::FormStudents(QList<UserData*> list,UserData *d)
{
    QVBoxLayout *FormLayout = new QVBoxLayout(this);
    id = d->id();


    qDebug() << d;
    BaseInfos = new BasicInfos(d);
    FormLayout->addWidget(BaseInfos);

    ParInfos = new ParentInfos(d);
    ParInfos->getParent()->addItem(tr("none"), 0);
    foreach (UserData* mud, list)
    ParInfos->getParent()->addItem(mud->surname()+" "+mud->name(), mud->id());

    ParInfos->getParent()->setCurrentIndex(ParInfos->getParent()->findData(d->relationship(), Qt::UserRole, Qt::MatchCaseSensitive));
    FormLayout->addWidget(ParInfos);

    SocInfos = new SocialInfos(d);
    FormLayout->addWidget(SocInfos);


    SchoInfos = new SchoolInfos(d);
    FormLayout->addWidget(SchoInfos);

    SuiInfos = new SuiviInfos(d);
    FormLayout->addWidget(SuiInfos);


    this->setLayout(FormLayout);
}
