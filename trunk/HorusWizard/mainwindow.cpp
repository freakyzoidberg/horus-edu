#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{



    ui->setupUi(this);
    ui->progressBar->reset();
    ui->progressBar->setMinimum(0);

    ui->progressBar_2->reset();

    connect(ui->pushButton, SIGNAL( clicked() ), this, SLOT( InstallServer() ) );
    connect(ui->pushButton_2, SIGNAL( clicked() ), this, SLOT( InstallClient() ) );


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InstallServer()
{
ui->progressBar->setMaximum( 100000);
for (int i = 0; i < 100001; i++) {
     ui->progressBar->setValue((int)((i)));

}
ui->label_3->setText("Server Done");
}

void MainWindow::InstallClient()
{
ui->progressBar->setMaximum( 100000);
for (int i = 0; i < 100001; i++) {
     ui->progressBar_2->setValue((int)((i)));
}

ui->label_4->setText("Client Done");
}

void MainWindow::done()
{
    //timer.start( 1 );

    //lineEdit->setText( path );
}
