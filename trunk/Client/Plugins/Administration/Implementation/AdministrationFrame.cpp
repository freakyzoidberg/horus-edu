#include "AdministrationFrame.h"
#include <QDebug>

AdministrationFrame::AdministrationFrame() : QWidget()
{
    setupUi(this);
    this->setLayout(this->mainLayout);
    this->fillTab();
}

void AdministrationFrame::fillTab()
{
    cF = new ClassFrame();
    uF = new UserFrame();
    teachF = new TeacherFrame();
    sF = new ClassRoomFrame();
    fF = new FileFrame();
	connect(cF, SIGNAL(sender(const QString &sender, PluginPacket *packet)), this, SLOT(sender(const QString &sender, PluginPacket *packet)));
	connect(uF, SIGNAL(sender(const QString &sender, PluginPacket *packet)), this, SLOT(sender(const QString &sender, PluginPacket *packet)));
	connect(teachF, SIGNAL(sender(const QString &sender, PluginPacket *packet)), this, SLOT(sender(const QString &sender, PluginPacket *packet)));
	connect(sF, SIGNAL(sender(const QString &sender, PluginPacket *packet)), this, SLOT(sender(const QString &sender, PluginPacket *packet)));
	connect(fF, SIGNAL(sender(const QString &sender, PluginPacket *packet)), this, SLOT(sender(const QString &sender, PluginPacket *packet)));
    this->classLayout->addWidget(cF, 0, 0);
    this->classTab->setLayout(classLayout);
    this->studentLayout->addWidget(uF, 0, 0);
    this->studentTab->setLayout(studentLayout);
    this->teacherLayout->addWidget(teachF, 0, 0);
    this->teacherTab->setLayout(teacherLayout);
    this->salleLayout->addWidget(sF, 0, 0);
    this->salleTab->setLayout(salleLayout);
    //this->cursusLayout->addWidget(sF, 0, 0); // Why add ClassRoomFrame in Cursus ???? (Valentin)
    //this->cursusTab->setLayout(cursusLayout);
    this->fileLayout->addWidget(fF, 0, 0);
    this->fileTab->setLayout(fileLayout);
}

void AdministrationFrame::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}
void AdministrationFrame::sender(const QString &sender, PluginPacket *packet)
{
    qDebug() << "here";
    this->packetSender.enqueue(sender);
	emit send(packet);
}

void AdministrationFrame::packetManager(QVariantHash response)
{
	QString sender;

	sender = packetSender.dequeue();
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
        if (sender == "students")
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

