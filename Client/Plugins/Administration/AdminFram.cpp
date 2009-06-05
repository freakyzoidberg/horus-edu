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
    cF = new ClassFram(this->res);
    this->classLayout->addWidget(cF, 0, 0);
    this->classTab->setLayout(classLayout);
    uF = new UserFram(this->res, this);
    this->studentLayout->addWidget(uF, 0, 0);
    this->studentTab->setLayout(studentLayout);
    teachF = new TeacherFram(this->res, this);
    this->teacherLayout->addWidget(teachF, 0, 0);
    this->teacherTab->setLayout(teacherLayout);
    sF = new SalleFram(this->res);
    this->salleLayout->addWidget(sF, 0, 0);
    this->salleTab->setLayout(salleLayout);
    sF = new SalleFram(this->res);
    this->cursusLayout->addWidget(sF, 0, 0);
    this->cursusTab->setLayout(cursusLayout);
    fF = new FileFram(this->res);
    this->fileLayout->addWidget(fF, 0, 0);
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
void AdminFram::sender(const QString &sender)
{
    qDebug() << "here";
    this->packetSender.enqueue(sender);
}

void AdminFram::packetManager(QVariantHash response)
{
    if (response["Request"] == "listUsers")
    {
        this->uF->readResponse(response);
        this->teachF->readResponse(response);
    }
    else if (response["Request"] == "changePassword" ||
        response["Request"] == "setUserInfo" ||
        response["Request"] == "createNewUser" ||
        response["Request"] == "disableUser")
    {
        if (packetSender.dequeue() == "students")
            this->uF->readResponse(response);
        else
            this->teachF->readResponse(response);
    }
    else
    {
        qDebug() << "receive Arbre";
        this->uF->readResponse(response);
    }
}

