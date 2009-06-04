#include "MainFrameWidget.h"

#include <QGridLayout>
#include <QPushButton>
#include "../../../IClient.h"
#include <QDebug>

MainFrameWidget::MainFrameWidget(MainFrame *plugin) : QFrame::QFrame()
{
    QGridLayout *layout = new QGridLayout;
    IClientPlugin *course = 0;
    QPushButton *button;

    this->plugin = plugin;
    ui.setupUi(this);
    course = plugin->client->getPlugin("Course");
    qDebug() << course;
    if (course)
    {
        button = new QPushButton("My Lessons");
        layout->addWidget(button, 1, 0);
        layout->setRowStretch(1, 0);
        connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    }
    layout->setRowStretch(0, 1);
    this->setLayout(layout);
}

void MainFrameWidget::buttonClicked()
{
    this->plugin->display->setCentralWidget((qobject_cast<IDisplayablePlugin *>(this->plugin->client->getPlugin("Course")))->getWidget());
}
