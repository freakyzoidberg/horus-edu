#include "FormStudents.h"

FormStudents::FormStudents()
{
    QVBoxLayout *FormLayout = new QVBoxLayout(this);

    BasicInfos *BaseInfos = new BasicInfos();

    FormLayout->addWidget(BaseInfos);


    this->setLayout(FormLayout);
}

FormStudents::FormStudents(UserData *)
{
    QVBoxLayout *FormLayout = new QVBoxLayout(this);

    BasicInfos *BaseInfos = new BasicInfos();

    FormLayout->addWidget(BaseInfos);


    this->setLayout(FormLayout);
}
