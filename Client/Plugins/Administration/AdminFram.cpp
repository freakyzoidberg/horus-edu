#include "AdminFram.h"
#include <QDebug>

AdminFram::AdminFram(INetwork *reseau) : QWidget()
{

    this->res = reseau;
    setupUi(this);
    this->setLayout(this->mainLayout);
    this->fillTab();

}

void AdminFram::fillTab()
{
    tF = new TreeFram(this->res);
    cF = new ClassFram(this->res);
    this->classLayout->addWidget(tF, 0, 0);
    this->classLayout->addWidget(cF, 0, 1);
    this->classLayout->setColumnStretch(0, 1);
    this->classLayout->setColumnStretch(1, 3);
    this->classTab->setLayout(classLayout);
    tF = new TreeFram(this->res);
    uF = new UserFram(this->res);
    this->studentLayout->addWidget(tF, 0, 0);
    this->studentLayout->addWidget(uF, 0, 1);
    this->studentLayout->setColumnStretch(0, 1);
    this->studentLayout->setColumnStretch(1, 3);
    this->studentTab->setLayout(studentLayout);
    tF = new TreeFram(this->res);
    teachF = new TeacherFram(this->res);
    this->teacherLayout->addWidget(tF, 0, 0);
    this->teacherLayout->addWidget(teachF, 0, 1);
    this->teacherLayout->setColumnStretch(0, 1);
    this->teacherLayout->setColumnStretch(1, 3);
    this->teacherTab->setLayout(teacherLayout);
    tF = new TreeFram(this->res);
    sF = new SalleFram(this->res);
    this->salleLayout->addWidget(tF, 0, 0);
    this->salleLayout->addWidget(sF, 0, 1);
    this->salleLayout->setColumnStretch(0, 1);
    this->salleLayout->setColumnStretch(1, 3);
    this->salleTab->setLayout(salleLayout);
    tF = new TreeFram(this->res);
    sF = new SalleFram(this->res);
    this->cursusLayout->addWidget(tF, 0, 0);
    this->cursusLayout->addWidget(sF, 0, 1);
    this->cursusLayout->setColumnStretch(0, 1);
    this->cursusLayout->setColumnStretch(1, 3);
    this->cursusTab->setLayout(cursusLayout);
    tF = new TreeFram(this->res);
    fF = new FileFram(this->res);
    this->fileLayout->addWidget(tF, 0, 0);
    this->fileLayout->addWidget(fF, 0, 1);
    this->fileLayout->setColumnStretch(0, 1);
    this->fileLayout->setColumnStretch(1, 3);
    this->fileTab->setLayout(fileLayout);
}

void AdminFram::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}

void AdminFram::packetManager(QVariantHash response)
{
    if (response["Request"] == "changePassword" ||
        response["Request"] == "listUsers" ||
        response["Request"] == "setUserInfo" ||
        response["Request"] == "createNewUser" ||
        response["Request"] == "disableUser")
    {
        this->uF->readResponse(response);
    }
    else
    {
        this->tF->readResponse(response);
    }
}
