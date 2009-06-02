#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTreeWidget>
#include <QPushButton>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    QWidget fenetre;
    QPushButton *french = new QPushButton("french");
    QPushButton *english = new QPushButton("english");

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(french);
    layout->addWidget(english);
    fenetre.setLayout(layout);
    fenetre.show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::explorer()
{
    //build tree
QTreeWidget *Tree = new QTreeWidget(this->centralWidget());

Tree->setMaximumWidth(200);
Tree->setColumnCount(1);
Tree->setHeaderLabel("matiere");

//build index
QTreeWidgetItem *cours1 = new QTreeWidgetItem(Tree);
cours1->setText(0,"cours 1");

//build child
QTreeWidgetItem *lesson1 = new QTreeWidgetItem(cours1);
lesson1->setText(0,"lesson 1");

QTreeWidgetItem *cours2 = new QTreeWidgetItem;
cours2->setText(0,"cours 2");

Tree->insertTopLevelItem(0, cours1);
Tree->insertTopLevelItem(1, cours2);

Tree->show();
}

void    MainWindow::ViewLesson()
{
   QTreeWidget *Tree = new QTreeWidget;
Tree->setColumnCount(1);
Tree->setHeaderLabel("test");
Tree->show();
}
