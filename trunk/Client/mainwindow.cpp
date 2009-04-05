#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    cM = new ConnectionManager();
    ui->setupUi(this);
    this->setWindowTitle("Horus");
    ReadSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}


 void MainWindow::WriteSettings()
 {
     QSettings settings;

     settings.beginGroup("MainWindow");
     settings.setValue("size", size());
     settings.setValue("pos", pos());
     settings.endGroup();
     settings.sync();
 }

 void MainWindow::ReadSettings()
 {
     QSettings settings;

     settings.beginGroup("MainWindow");
     resize(settings.value("size", QSize(400, 400)).toSize());
     move(settings.value("pos", QPoint(200, 200)).toPoint());
     settings.endGroup();
 }

 void MainWindow::closeEvent(QCloseEvent *event)
 {
    WriteSettings();
//    event->accept();
 }


void MainWindow::on_ConnectButton_clicked()
{
    cM->ConnectTo("127.0.0.1", 42421);
}
