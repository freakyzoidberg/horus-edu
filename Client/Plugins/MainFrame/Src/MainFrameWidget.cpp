#include "MainFrameWidget.h"

#include "../../../Common/PluginManager.h"
#include "../../../Common/UserDataPlugin.h"
#include "../../../Common/UserData.h"

#include <QPushButton>
#include <QDebug>
#include <QLabel>
#include <QDateTime>

MainFrameWidget::MainFrameWidget(MainFrame *_plugin) : QFrame::QFrame()
{
    this->layout = new QGridLayout;
    Plugin *course = 0;
    QPushButton *button;

    this->plugin = _plugin;
    ui.setupUi(this);
    course = PluginManager().findPlugin<DisplayablePlugin*>("Course");
    if (course)
    {
        button = new QPushButton("My Lessons");
        layout->addWidget(button, 2, 0);
        layout->setRowStretch(2, 0);
        connect(button, SIGNAL(clicked()), plugin, SLOT(courseClicked()));
    }
    layout->setRowStretch(0, 0);
    layout->setRowStretch(1, 1);
    this->setLayout(layout);
}

void    MainFrameWidget::updateInfos()
{
    qDebug() << "MainFrameWidget::updateInfos";

    UserDataPlugin* p = PluginManager().findPlugin<UserDataPlugin*>();
    if ( ! p)
        return;

    UserData* user = p->currentUser;
    qDebug() << "MainFrameWidget::updateInfos";

    if ( ! user)
        return;

    qDebug() << "MainFrameWidget::updateInfos";
    this->layout->addWidget(new QLabel("Connected as " + user->login, this), 0, 0);


    //    if (userInfo.value("last_login").toDateTime().isValid())
//        this->layout->addWidget(new QLabel("Last login " + user->, this), 0, 1);
}
