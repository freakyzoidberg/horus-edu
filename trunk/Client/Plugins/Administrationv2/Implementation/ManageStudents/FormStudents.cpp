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

    this->setLayout(FormLayout);
}

FormStudents::FormStudents(UserData *d)
{
    QVBoxLayout *FormLayout = new QVBoxLayout(this);

    BasicInfos *BaseInfos = new BasicInfos();

    FormLayout->addWidget(BaseInfos);


    this->setLayout(FormLayout);
}
