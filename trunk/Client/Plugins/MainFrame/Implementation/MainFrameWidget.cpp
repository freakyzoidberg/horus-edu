#include "MainFrameWidget.h"

#include <QGridLayout>
#include <QPushButton>

MainFrameWidget::MainFrameWidget() : QFrame::QFrame()
{
    QGridLayout *layout = new QGridLayout;

    ui.setupUi(this);
    layout->addWidget(new QPushButton("Horus the Chorus"), 0, 0, 1, 2);
    layout->addWidget(new QPushButton("My last classes"), 1, 0);
    layout->addWidget(new QPushButton("My last mails"), 1, 1);
    layout->addWidget(new QPushButton("My calendar"), 2, 0);
    layout->addWidget(new QPushButton("Ma grade / Marks"), 2, 1);
    this->setLayout(layout);
}
