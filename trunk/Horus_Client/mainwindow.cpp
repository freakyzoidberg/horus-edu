#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{

     ui->setupUi(this);
    this->setWindowTitle("Horus");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ConnectButton_clicked()
{
    QMessageBox msgBox;

    msgBox.setText("Connected to the server!!!");
    msgBox.exec();
}
