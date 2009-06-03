#include "CourseWidget.h"

CourseWidget::CourseWidget(): QFrame::QFrame()
{
    this->fenetre = new QWidget(this);
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

CourseWidget::~CourseWidget()
{

}

void CourseWidget::explorer()
{

    //build tree
this->tree = new QTreeWidget(this->fenetre);
this->tree->resize(150,200);

tree->setMaximumWidth(200);
tree->setColumnCount(1);
tree->setHeaderLabel("matiere");

//build index
QTreeWidgetItem *cours1 = new QTreeWidgetItem(tree);
cours1->setText(0,"cours 1");

//build child
QTreeWidgetItem *lesson1 = new QTreeWidgetItem(cours1);
lesson1->setText(0,"lesson 1");

QTreeWidgetItem *cours2 = new QTreeWidgetItem;
cours2->setText(0,"cours 2");

tree->insertTopLevelItem(0, cours1);
tree->insertTopLevelItem(1, cours2);
tree->show();
}

void    CourseWidget::ViewLesson()
{
   QTreeWidget *tree = new QTreeWidget;
tree->setColumnCount(1);
tree->setHeaderLabel("test");
tree->show();
}
