#include "CourseWidget.h"

CourseWidget::CourseWidget()
{
 this->fenetre = new QWidget();
    this->fenetre->resize(640,480);


/*
    this->french = new QPushButton("french");
    this->english = new QPushButton("english");
    this->math = new QPushButton("math");
    this->svt = new QPushButton("svt");

    QHBoxLayout *layout = new QHBoxLayout;

    layout->addWidget(french);
    layout->addWidget(english);
    layout->addWidget(math);
    layout->addWidget(svt);

    fenetre->setLayout(layout);
    */
    fenetre->move(10, 200);
    fenetre->show();
   /*
    QObject::connect(this->french, SIGNAL(clicked()), this, SLOT(explorer()));
    QObject::connect(this->english, SIGNAL(clicked()), this, SLOT(explorer()));
    QObject::connect(this->math, SIGNAL(clicked()), this, SLOT(explorer()));
    QObject::connect(this->svt, SIGNAL(clicked()), this, SLOT(explorer()));
    */
}

~CourseWidget::CourseWidget()
{

}
