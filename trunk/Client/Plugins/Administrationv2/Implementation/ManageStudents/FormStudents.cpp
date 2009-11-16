#include "FormStudents.h"

FormStudents::FormStudents()
{
    QVBoxLayout *FormLayout = new QVBoxLayout(this);

    BaseInfos = new BasicInfos();
    FormLayout->addWidget(BaseInfos);

    SocInfos = new SocialInfos();
    FormLayout->addWidget(SocInfos);


    SchoInfos = new SchoolInfos();
    FormLayout->addWidget(SchoInfos);

    SuiInfos = new SuiviInfos();
    FormLayout->addWidget(SuiInfos);
    id = 0;
    this->setLayout(FormLayout);
}

FormStudents::FormStudents(UserData *d)
{
    QVBoxLayout *FormLayout = new QVBoxLayout(this);
    id = d->id();

    BaseInfos = new BasicInfos(d);
    FormLayout->addWidget(BaseInfos);

    SocInfos = new SocialInfos(d);
    FormLayout->addWidget(SocInfos);


    SchoInfos = new SchoolInfos(d);
    FormLayout->addWidget(SchoInfos);

    SuiInfos = new SuiviInfos(d);
    FormLayout->addWidget(SuiInfos);


    this->setLayout(FormLayout);
}
