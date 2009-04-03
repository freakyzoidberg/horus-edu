#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
     hostLabel = new QLabel(tr("&Server name:"));
     portLabel = new QLabel(tr("S&erver port:"));

     hostLineEdit = new QLineEdit("Localhost");
     portLineEdit = new QLineEdit;
     portLineEdit->setValidator(new QIntValidator(1, 65535, this));

     hostLabel->setBuddy(hostLineEdit);
     portLabel->setBuddy(portLineEdit);
    getFortuneButton = new QPushButton(tr("Connect"));
    tcpSocket = new QTcpSocket(this);

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
