#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    vecclient.clear();
    vecserver.clear();


    ui->setupUi(this);
    ui->progressBar->reset();
    ui->progressBar->setMinimum(0);
    ui->progressBar_2->reset();

    addvecserver("file1", "bin");
    addvecserver("file2", "bin");
    addvecserver("file3", "bin");
    addvecserver("file1", "bin");
    addvecclient("file3", "bin");
    addvecclient("file3", "bin");
    addvecclient("file3", "bin");

    connect(ui->pushButton, SIGNAL( clicked() ), this, SLOT( InstallServer() ) );
    connect(ui->pushButton_2, SIGNAL( clicked() ), this, SLOT( InstallClient() ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InstallServer()
{
ui->progressBar->setMaximum(vecserver.count() - 1);
QFile file;
for (int i = 0; i < vecserver.count(); i++) {
    file.setFileName(vecserver.at(i).name);
    ui->label_3->setText(vecserver.at(i).name);
     ui->progressBar->setValue((int)((i)));

}
ui->label_3->setText("Server Done");
}

void MainWindow::InstallClient()
{
    QFile file;
ui->progressBar_2->setMaximum((vecclient.count()) - 1);
for (int i = 0; i < vecclient.count() ; i++) {
    file.setFileName(vecclient.at(i).name);
     ui->progressBar_2->setValue((int)((i)));
}

ui->label_4->setText("Client Done");
}

void MainWindow::done()
{
    //timer.start( 1 );

    //lineEdit->setText( path );
}

void MainWindow::addvecclient(QString name, QString folder)
{
    contentstruct tmpstruct;
    tmpstruct.name = name;
    tmpstruct.folder = folder;
    vecclient.append(tmpstruct);
}
void MainWindow::addvecserver(QString name, QString folder)
{
    contentstruct tmpstruct;
    tmpstruct.name = name;
    tmpstruct.folder = folder;
    vecserver.append(tmpstruct);
}
