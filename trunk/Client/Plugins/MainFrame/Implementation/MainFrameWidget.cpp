#include "MainFrameWidget.h"

#include "../../../Common/PluginManager.h"

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
        connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    }
    layout->setRowStretch(0, 0);
    layout->setRowStretch(1, 1);
    this->setLayout(layout);
}

void    MainFrameWidget::updateInfos(QHash<QString, QVariant> userInfo)
{
    qDebug() << userInfo;
    this->layout->addWidget(new QLabel("Connected as " + userInfo.value("login").toString(), this), 0, 0);
    if (userInfo.value("last_login").toDateTime().isValid())
        this->layout->addWidget(new QLabel("Last login " + userInfo.value("last_login").toDateTime().toString(), this), 0, 1);
}

void MainFrameWidget::buttonClicked()
{
    this->plugin->setCentralWidget(PluginManager().findPlugin<DisplayablePlugin*>("Course")->getWidget());
}
